#pragma once

#include "RealValueBase.h"
#include "StringType.h"
#include <string>

class StringValue : public RealValueBase<StringValue, StringType> {
public:
    StringValue(std::string value);

    std::string printable_str() const override;
    void visit(ValueVisitor& visitor) override;
};
