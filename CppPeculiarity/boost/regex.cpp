#include <boost/regex.hpp>
#include <iostream>

int main() {
    boost::regex email_regex("([a-zA-Z0-9._%+-]+)@([a-zA-Z0-9.-]+)\\.([a-zA-Z]{2,4})");
    std::string text = "Contact us at support@example.com for assistance.";

    boost::smatch match;
    if (boost::regex_search(text, match, email_regex)) {
        std::cout << "Email found: " << match[0] << std::endl;
    }
}
