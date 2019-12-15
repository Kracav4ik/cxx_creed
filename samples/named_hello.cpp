#include <iostream>
#include <string>

int main() {
    std::cout << "Hello, what is your name?" << std::endl;
    std::string name;
    std::cin >> name;
    std::cout << "Have a good day, " << name << "!" << std::endl;
    return 0;
}
