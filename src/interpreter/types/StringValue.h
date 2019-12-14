#pragma once

#include "RealValueBase.h"
#include <string>

class StringType;
class StringValue : public RealValueBase<StringValue, StringType> {
public:
    StringValue(std::string value);
    std::string get_value() const;

    std::string printable_str() const override;
    std::shared_ptr<StringType> get_real_type() const override;

private:
    std::string _value;
};
