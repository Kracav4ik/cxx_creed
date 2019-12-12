#include "ArithmeticException.h"

ArithmeticException::ArithmeticException(std::string msg, int result) : RuntimeException(std::move(msg)), _result(result) {
}

int ArithmeticException::get_result() const noexcept {
    return _result;
}
