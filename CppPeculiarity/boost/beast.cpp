#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <iostream>

int main() {
    namespace beast = boost::beast;
    namespace http = beast::http;

    beast::error_code ec;
    beast::tcp_stream stream;

    stream.connect("www.boost.org", "http", ec);
    if (ec) {
        std::cerr << "Failed to connect: " << ec.message() << std::endl;
        return 1;
    }

    http::request<http::string_body> req{http::verb::get, "/", 11};
    req.set(http::field::host, "www.boost.org");
    req.set(http::field::user_agent, "Beast");

    http::write(stream, req);

    beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;

    http::read(stream, buffer, res, ec);

    if (ec) {
        std::cerr << "Failed to read: " << ec.message() << std::endl;
        return 1;
    }

    std::cout << res << std::endl;
}