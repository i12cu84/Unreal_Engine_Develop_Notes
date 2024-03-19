#include <iostream>
#include <boost/bimap.hpp>

int main()
{
    boost::bimap<std::string, int> bm;

    bm.insert({"one", 1});
    bm.insert({"two", 2});
    bm.insert({"three", 3});

    std::cout << "bm[\"one\"] = " << bm.left.at("one") << "\n";
    std::cout << "bm.right[2] = " << bm.right.at(2) << "\n";

    return 0;
}
