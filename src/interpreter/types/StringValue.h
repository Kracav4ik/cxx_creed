#pragma once

#include "RealValueBase.h"
#include <string>

class StringType;
class StringValue : public RealValueBase<StringValue, StringType> {
public:
    StringValue(std::string value);
    std::string get_value() const;

    std::string printable_str() const override;

private:
    std::string _value;
};
