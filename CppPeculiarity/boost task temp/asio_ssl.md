Boost.Asio SSL：使用Boost.Asio进行安全套接字层（SSL）通信的示例。

cpp
Copy code
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>

int main() {
    boost::asio::io_service io_service;
    boost::asio::ssl::context ssl_context(io_service, boost::asio::ssl::context::sslv23);

    // Configure SSL context (e.g., load certificates)

    boost::asio::ssl::stream<boost::asio::ip::tcp::socket> ssl_socket(io_service, ssl_context);
    ssl_socket.lowest_layer().connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 443));

    // Perform SSL communication

    std::cout << "SSL communication completed" << std::endl;
}