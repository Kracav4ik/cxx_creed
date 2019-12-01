#pragma once

#include "Printer.h"

class ConsolePrinter : public Printer {
public:
    void print_message(const std::string& text) override;
    void print_error(const std::string& text) override;
};
