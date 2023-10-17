#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>

int main() {
    boost::property_tree::ptree pt;
    boost::property_tree::ini_parser::read_ini("config.ini", pt);

    // Modify and save the configuration
    pt.put("Section1.Value1", 42);

    // Print modified property grid
    boost::property_tree::ini_parser::write_ini("config_modified.ini", pt);
}
