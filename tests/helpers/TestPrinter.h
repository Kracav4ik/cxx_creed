#pragma once

#include "Printer.h"
#include <sstream>

class TestPrinter : public Printer {
public:
    void print_message(const std::string& text) override;
    void print_error(const std::string& text) override;

    std::string str() const;

private:
    std::stringstream _buf;
};
