#pragma once
#include "RealTypeBase.h"
#include <string>

class StringValue;
class StringType : public RealTypeBase<StringValue, std::string> {
public:
    bool is_true(const StringValue& value) const override;
    ValuePtr create_value(const std::string& value) const override;
    std::string type_name() const override;

    static std::shared_ptr<StringType> get();

private:
    StringType();

    static bool is_true_value(const std::string& val);
};
