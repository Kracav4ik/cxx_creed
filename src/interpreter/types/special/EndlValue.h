#pragma once

#include "SpecialValue.h"
#include <memory>

class EndlType;
template <typename TypeValue, typename TypeClass> class SpecialType;

class EndlValue : public SpecialValue<EndlType>, public std::enable_shared_from_this<EndlValue> {
friend class SpecialType<EndlValue, EndlType>;
public:
    std::string printable_str() const override;

private:
    EndlValue() = default;
};
