#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <bitset>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "../proto/messages.pb.h"

using boost::asio::ip::tcp;
using namespace TestTask::Messages;

class session
    : public std::enable_shared_from_this<session>
{
    public:
        session(tcp::socket socket, boost::asio::deadline_timer timer)
            : socket_(std::move(socket)), timer_(std::move(timer)){
            }

        void start(){
            // #TODO
            std::cout << "Connected " << socket << std::endl;

            do_read();
        }

    private:
        void do_read()
        {
            auto self(shared_from_this());
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
                [this, self](boost::system::error_code ec, std::size_t length)
                {
                    if ((boost::asio::error::eof == ec) ||
                    (boost::asio::error::connection_reset == ec))
                    {
                    std::cout << "Disconnect" << std::endl;
                    }
                    if (!ec){
                        message_ = new WrapperMessage();
                        message_->ParseFromString(data_);
                        std::cout << message_->request_for_slow_response().time_in_seconds_to_sleep() << std::endl;
                        slow_write();
                    }
                });

            //timer_.expires_from_now(boost::posix_time::seconds(atoi(data_)));
            //timer_.async_wait([this, self](boost::system::error_code ec) {
                //if (!ec)
                //    std::cout << "Read msg" << socket << " data " << atoi(data_) << std::endl;
                //});
        }

        void slow_write(){
            auto self(shared_from_this());
            WrapperMessage* new_msg = new WrapperMessage();
            SlowResponse* slow = new SlowResponse();
            slow->set_connected_client_count(5);
            new_msg->set_allocated_slow_response(slow);
            timer_.expires_from_now(boost::posix_time::seconds(message_->request_for_slow_response().time_in_seconds_to_sleep()));
            timer_.async_wait([this, self, new_msg](const boost::system::error_code &ec){
                if (!ec){
                    do_write(std::move(new_msg));
            }});
        }

        void do_write(WrapperMessage* respond_message){
            auto self(shared_from_this());
            std::string request;
            respond_message->SerializeToString(&request);

            boost::asio::async_write(socket_, boost::asio::buffer(request.c_str(), request.size()),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
            {
                if ((boost::asio::error::eof == ec) ||
                (boost::asio::error::connection_reset == ec))
                {
                std::cout << "Disconnect" << std::endl;
                }
                if (!ec)
                {
                    do_read();
                }
            });
        }
    enum { max_length = 1024 };
    char data_[max_length];
    WrapperMessage* message_;
    tcp::socket socket_;
    boost::asio::deadline_timer timer_;
};

class tcp_server
{
    public:
        tcp_server(boost::asio::io_context& io_context, short port)
            : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), timer_(io_context){
            do_accept();
        }
    private:
        void do_accept(){
            acceptor_.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket){
                    if (!ec){
                        std::make_shared<session>(std::move(socket), std::move(timer_))->start();
                    }
                    do_accept();
                });
        }

    tcp::acceptor acceptor_;
    boost::asio::deadline_timer timer_;
};

int main(int argc, char* argv[])
{
    try
    {
        std::ifstream port_ini("src/port.ini");

        std::string port;

        if ( port_ini.is_open() )
            port_ini >> port; 
        else
            std::cerr << "Error while oppening the file" << std::endl;;

        boost::asio::io_context io_context;

        tcp_server server(io_context, std::stoi(port));

        io_context.run();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}