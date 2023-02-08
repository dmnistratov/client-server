#include <cstdlib>
#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "../../proto/messages.pb.h"
#include "../common/DelimitedMessagesStreamParser.h"

using boost::asio::ip::tcp;
using namespace TestTask::Messages;

class session
    : public std::enable_shared_from_this<session>
{
    public:
        session(tcp::socket socket, boost::asio::deadline_timer timer, int* connections)
            : socket_(std::move(socket)), timer_(std::move(timer)), connections_(connections){
            }

        void start(){
            write_log("Client connected. ");
            *connections_ += 1;
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
                        write_log("Client disconnected.");
                        *connections_ -= 1;
                    }
                    if (!ec){
                        //message_ = new WrapperMessage();
                        //message_->ParseFromString(data_);
                        
                        auto parser = DelimitedMessagesStreamParser<WrapperMessage>();
                        auto messages = std::vector<const std::shared_ptr<const WrapperMessage>>();
                        for (const char byte : data_)
                        {
                            const std::list<DelimitedMessagesStreamParser<WrapperMessage>::PointerToConstValue> parsedMessages = parser.parse(std::string(1, byte));
                            for (const DelimitedMessagesStreamParser<WrapperMessage>::PointerToConstValue value : parsedMessages)
                            {
                                messages.push_back(value);
                            }
                            // /*std::list<std::shared_ptr<const WrapperMessage>>*/auto parsedMessages = parser.parse(std::string(1, byte));
                            /*const std::list<std::shared_ptr<const WrapperMessage>>& parsedMessages = parser.parse(std::string(1, byte));
                            for (std::shared_ptr<const WrapperMessage> value : parsedMessages)
                            {
                                messages.push_back(*value);
                            }*/
                        }
                        
                        //std::list<std::shared_ptr<const WrapperMessage>> messages = parser.parse(data_);

                        for (auto msg : messages)
                        {
                            if (msg->has_request_for_fast_response())
                            {
                                write_log("Client send request for fast response.");
                                fast_response();
                                return;
                            }

                            if (msg->has_request_for_slow_response())
                            {
                                write_log("Client send request for slow response. Time to sleep = " + std::to_string(msg->request_for_slow_response().time_in_seconds_to_sleep()));
                                slow_write();
                                return;
                            }
                        }
                    }
                });
        }

        void fast_response()
        {
            auto self(shared_from_this());
            WrapperMessage* response = new WrapperMessage();
            FastResponse* fast_response = new FastResponse();
            
            auto datetime = boost::posix_time::microsec_clock::local_time();
            auto iso_datetime_string = boost::posix_time::to_iso_string(datetime);
            auto iso_datetime_string_for_FastResponse = iso_datetime_string.substr(0, iso_datetime_string.find('.') + 4); // 4 because .xxx

            fast_response->set_current_date_time(iso_datetime_string_for_FastResponse);
            response->set_allocated_fast_response(fast_response);
            do_write(std::move(response));
            write_log("Server send fast response.");
        }

        void slow_write(){
            auto self(shared_from_this());
            WrapperMessage* new_msg = new WrapperMessage();
            SlowResponse* slow = new SlowResponse();
            slow->set_connected_client_count(*connections_);
            new_msg->set_allocated_slow_response(slow);
            timer_.expires_from_now(boost::posix_time::seconds(message_->request_for_slow_response().time_in_seconds_to_sleep()));
            timer_.async_wait([this, self, new_msg](const boost::system::error_code &ec){
                if (!ec){
                    write_log("Server send slow response with count connections = " + std::to_string(*connections_));
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
                    write_log("Client disconnected.");
                    *connections_ -= 1;
                }
                if (!ec)
                {
                    do_read();
                }
            });
        }

        void write_log(std::string msg)
        {
            std::ofstream log("log.log", std::ios_base::app);

            if (log.is_open())
            {
                auto time = boost::posix_time::microsec_clock::local_time();
                std::cout << time << " [LOG]: " << msg << std::endl;
                log << time << " [LOG]: " << msg << std::endl;
            }

            log.close();
        }

    enum { max_length = 1024 };
    char data_[max_length];
    int* connections_;
    WrapperMessage* message_;
    tcp::socket socket_;
    boost::asio::deadline_timer timer_;
};

class tcp_server
{
    public:
        tcp_server(boost::asio::io_context& io_context, short port)
            : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), timer_(io_context), total_connections_(new int(0)){
            do_accept();
        }
    private:
        void do_accept(){
            acceptor_.async_accept(
                [this](boost::system::error_code ec, tcp::socket socket){
                    if (!ec){
                        std::make_shared<session>(std::move(socket), std::move(timer_), total_connections_)->start();
                    }
                    do_accept();
                });
        }

    int* total_connections_;
    tcp::acceptor acceptor_;
    boost::asio::deadline_timer timer_;
};

int main(int argc, char* argv[])
{
    try
    {
        std::cout << __cplusplus << std::endl;
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