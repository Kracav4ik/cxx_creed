#include "util.h"

#include <iostream>

int main() {
    std::string text = read_file("../src/main.cpp");
    std::cout << "----------\n" << text << "\n----------" << std::endl;
    return 0;
}
