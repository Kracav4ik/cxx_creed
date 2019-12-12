#pragma once

#include "RuntimeException.h"

class ArithmeticException : public RuntimeException {
public:
    explicit ArithmeticException(std::string msg, int result);
    int get_result() const noexcept;

private:
    int _result;
};
