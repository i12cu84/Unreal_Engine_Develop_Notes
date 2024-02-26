#include <iostream>
#include <string>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

int main()
{
    std::string input = "1 + 2 * 3";
    int result;

    auto it = input.begin();
    qi::phrase_parse(it, input.end(),
                     qi::int_ >> *(('+' >> qi::int_) | ('*' >> qi::int_)),
                     qi::space, result);

    std::cout << "result = " << result << "\n";

    return 0;
}
