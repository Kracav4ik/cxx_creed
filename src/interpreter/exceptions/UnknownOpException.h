#pragma once

#include "RuntimeException.h"

class UnknownOpException : public RuntimeException {
public:
    explicit UnknownOpException(std::string msg);
};
