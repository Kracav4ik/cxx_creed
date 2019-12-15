#pragma once

#include "RealValueBase.h"
#include "IntegerType.h"

class IntegerValue : public RealValueBase<IntegerValue, IntegerType> {
public:
    IntegerValue(int value);

    std::string printable_str() const override;
    void visit(ValueVisitor& visitor) override;
};
