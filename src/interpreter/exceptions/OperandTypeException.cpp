#include "OperandTypeException.h"

OperandTypeException::OperandTypeException(std::string msg) : RuntimeException(std::move(msg)) {
}
