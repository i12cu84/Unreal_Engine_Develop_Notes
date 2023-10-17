#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>

namespace beast = boost::beast;
namespace websocket = beast::websocket;

int main() {
    beast::error_code ec;
    beast::tcp_stream stream;

    stream.connect("echo.websocket.org", "http", ec);
    if (ec) {
        std::cerr << "Failed to connect: " << ec.message() << std::endl;
        return 1;
    }

    websocket::stream<beast::tcp_stream> ws(std::move(stream));
    ws.handshake("echo.websocket.org", "/", ec);
    if (ec) {
        std::cerr << "Handshake failed: " << ec.message() << std::endl;
        return 1;
    }

    ws.write(beast::buffers_cat("Hello, ", "WebSocket!"), ec);
    if (ec) {
        std::cerr << "Write failed: " << ec.message() << std::endl;
        return 1;
    }

    beast::multi_buffer buffer;
    ws.read(buffer, ec);
    if (ec) {
        std::cerr << "Read failed: " << ec.message() << std::endl;
        return 1;
    }

    std::cout << "Received: " << beast::make_printable(buffer.data()) << std::endl;
}
