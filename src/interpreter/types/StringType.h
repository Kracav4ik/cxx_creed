#pragma once
#include "RealTypeBase.h"
#include <string>

class StringValue;
class StringType : public RealTypeBase<StringValue, StringType, std::string> {
friend class SingletonType<StringType>;
public:
    bool is_true(const StringValue& value) const override;
    ValuePtr create_value(const std::string& value) const override;
    std::string type_name() const override;

private:
    StringType();

    static bool is_true_value(const std::string& val);
};
