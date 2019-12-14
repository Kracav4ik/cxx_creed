#include "CoutType.h"
#include "CoutValue.h"

ValuePtr CoutType::create_empty_value() const {
    static std::shared_ptr<CoutValue> res(new CoutValue());
    return res;
}

std::string CoutType::type_name() const {
    return "[std::cout pseudotype]";
}

std::shared_ptr<CoutType> CoutType::get() {
    static std::shared_ptr<CoutType> res(new CoutType());
    return res;
}
