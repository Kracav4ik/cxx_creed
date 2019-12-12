#pragma once

#include "RuntimeException.h"

class OperandTypeException : public RuntimeException {
public:
    explicit OperandTypeException(std::string msg);
};
