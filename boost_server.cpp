#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "messages.pb.h"

using boost::asio::ip::tcp;

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
                });
            std::cout << "data: " << atoi(data_) << std::endl;
            timer_.expires_from_now(boost::posix_time::seconds(atoi(data_)));
            timer_.async_wait([this, self](boost::system::error_code ec) {
                if (!ec)
                    std::cout << "Read msg" << socket << " data " << atoi(data_) << std::endl;
                });
        }

    enum { max_length = 1024 };
    char data_[max_length];
    tcp::socket socket_;
    std::string message_;
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
        if (argc != 2){
            std::cerr << "Usage: async_tcp_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        tcp_server server(io_context, std::atoi(argv[1]));

        io_context.run();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}