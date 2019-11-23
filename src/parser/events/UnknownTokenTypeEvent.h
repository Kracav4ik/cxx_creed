#pragma once

#include "ASTEvent.h"

#include <string>

struct UnknownTokenTypeEvent : public ASTEvent {
    explicit UnknownTokenTypeEvent(std::string token_type);

    void visit(EventVisitor& visitor) override;

    std::string token_type;
};
