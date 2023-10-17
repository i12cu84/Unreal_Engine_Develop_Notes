#include <boost/spirit/home/x3.hpp>
#include <iostream>

namespace x3 = boost::spirit::x3;

int main() {
    std::string json_data = "{ \"name\" : \"John\", \"age\" : 30 }";
    std::string name;
    int age;

    auto json_parser = x3::phrase_parse(json_data.begin(), json_data.end(),
        '{' >> "name" >> ':' >> x3::lexeme[+(x3::char_ - ',')] >> ',' >>
        "age" >> ':' >> x3::int_ >> '}', x3::space);

    if (json_parser) {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
}