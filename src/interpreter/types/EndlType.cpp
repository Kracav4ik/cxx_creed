#include "EndlType.h"
#include "EndlValue.h"

ValuePtr EndlType::create_empty_value() const {
    static std::shared_ptr<EndlValue> res(new EndlValue());
    return res;
}

std::string EndlType::type_name() const {
    return "[std::endl pseudotype]";
}

std::shared_ptr<EndlType> EndlType::get() {
    static std::shared_ptr<EndlType> res(new EndlType());
    return res;
}
