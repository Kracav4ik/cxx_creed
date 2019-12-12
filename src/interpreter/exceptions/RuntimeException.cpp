#include "RuntimeException.h"

RuntimeException::RuntimeException(std::string msg) : _msg(std::move(msg)) {
}

const char* RuntimeException::what() const noexcept {
    return _msg.c_str();
}

const std::string& RuntimeException::what_str() const noexcept {
    return _msg;
}
