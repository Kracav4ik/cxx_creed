#include "StringType.h"

#include "StringValue.h"
#include "RealValueBase.hpp"
#include "RealTypeBase.hpp"

bool StringType::is_true(const StringValue& value) const {
    return is_true_value(value.get_value());
}

ValuePtr StringType::create_value(const std::string& value) const {
    return std::make_shared<StringValue>(value);
}

std::string StringType::type_name() const {
    return "std::string";
}

StringType::StringType() {
    installBinaryOp("ADD", [](const std::string& a, const std::string& b) {
        return a + b;
    });
    installComparisonOps();
}

bool StringType::is_true_value(const std::string& val) {
    return !val.empty();
}
