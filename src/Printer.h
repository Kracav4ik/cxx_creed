#pragma once

#include <string>

class Printer {
public:
    virtual ~Printer() = default;

    virtual void print_message(const std::string& text) = 0;
    virtual void print_error(const std::string& text) = 0;
};
