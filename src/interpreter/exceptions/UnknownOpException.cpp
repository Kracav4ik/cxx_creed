#include "UnknownOpException.h"

UnknownOpException::UnknownOpException(std::string msg) : RuntimeException(std::move(msg)) {
}
