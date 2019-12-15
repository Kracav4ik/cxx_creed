#include "CinValue.h"
#include "CinType.h"
#include "SpecialValue.hpp"
#include "interpreter/types/ValueVisitor.h"
#include "interpreter/types/IntegerValue.h"
#include "interpreter/types/StringValue.h"
#include "interpreter/types/RealValueBase.hpp"

#include <iostream>

class CinVisitor : public ValueVisitor {
public:
    void visitIntegerValue(IntegerValue& value) override {
        int input;
        std::cin >> input;
        value.set_value(input);
    }

    void visitStringValue(StringValue& value) override {
        std::string input;
        std::cin >> input;
        value.set_value(input);
    }
};

ValuePtr CinValue::binary_op(const std::string& op, const ValuePtr& right) const {
    if (op == "RSHIFT") {
        CinVisitor visitor;
        right->visit(visitor);
        return std::const_pointer_cast<CinValue>(shared_from_this());
    }
    return SpecialValue::binary_op(op, right);
}

std::string CinValue::printable_str() const {
    return "[std::cin object]";
}
