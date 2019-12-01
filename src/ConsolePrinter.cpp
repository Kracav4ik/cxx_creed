#include "ConsolePrinter.h"
#include <iostream>

void ConsolePrinter::print_message(const std::string& text) {
    std::cout << text << std::endl;
    std::cout.flush();
}

void ConsolePrinter::print_error(const std::string& text) {
    std::cerr << text << std::endl;
    std::cerr.flush();
}
