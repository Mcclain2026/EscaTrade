#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "common/logger.hpp"

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

        ESCA_INFO("EscaTrade Server starting on port: {}", port);
        ESCA_DEBUG("Waiting for client connection...");

        tcp::socket socket(io_context);
        acceptor.accept(socket);
        
        ESCA_INFO("Client connected from: {}", socket.remote_endpoint().address().to_string());

        std::string message = "Connection Established\n";
        boost::asio::write(socket, boost::asio::buffer(message));

    }
    catch (std::exception& e) {
        ESCA_ERROR("Exception: {}", e.what());
    }

    return 0;
}