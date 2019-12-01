#include "TestPrinter.h"

void TestPrinter::print_message(const std::string& text) {
    _buf << text << std::endl;
}

void TestPrinter::print_error(const std::string& text) {
    _buf << text << std::endl;
}

std::string TestPrinter::str() const {
    return _buf.str();
}
