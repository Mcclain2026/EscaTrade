#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std::string_literals;

int main(int argc, char* argv[]) {
    try {
        std::string host{"127.0.0.1"s};
        std::string port{"1234"};

        if (argc == 3) { host = argv[1]; port = argv[2]; }

        boost::asio::io_context io_context;
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, port);

        tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        boost::system::error_code ec;
        boost::asio::streambuf receive_buffer;
        boost::asio::read_until(socket, receive_buffer, "\n", ec);

        if (!ec) {
            std::string data{
                boost::asio::buffers_begin(receive_buffer.data()),
                boost::asio::buffers_end(receive_buffer.data())
            };
            std::cout << "Server says: " << data;
        }
        else {
            std::cerr << "Read Error: " << ec.message() << std::endl;
        }

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}