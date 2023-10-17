#include <boost/asio.hpp>
#include <iostream>

int main() {
    boost::asio::io_service io_service;
    boost::asio::ip::tcp::acceptor acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 12345));

    boost::asio::ip::tcp::socket socket(io_service);
    acceptor.accept(socket);

    std::string message = "Hello, Boost.Asio!";
    boost::asio::write(socket, boost::asio::buffer(message));
}
