#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std::string_literals;

int main(int argc, char* argv[]) {
    try {

        unsigned short port{1234};

        if (argc == 2) {
            port = static_cast<unsigned short>(std::fflush(0), std::stoi(argv[1]));
        }

        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));

        std::cout << "EscaTrade Server started on port: " << port << std::endl;
        std::cout << "Waiting for connection..." << std::endl;

        tcp::socket socket(io_context);
        acceptor.accept(socket);

        std::cout << "Client connected from: " << socket.remote_endpoint().address().to_string() << std::endl;

        std::string message = "Connection Established\n";
        boost::asio::write(socket, boost::asio::buffer(message));

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}