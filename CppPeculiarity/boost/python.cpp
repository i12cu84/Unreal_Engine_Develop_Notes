#include <boost/python.hpp>

int add(int a, int b) {
    return a + b;
}

BOOST_PYTHON_MODULE(example) {
    using namespace boost::python;
    def("add", add);
}
