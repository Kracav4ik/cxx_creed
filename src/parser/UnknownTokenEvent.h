#pragma once

#include "ASTEvent.h"

#include <string>

struct UnknownTokenEvent : public ASTEvent {
    explicit UnknownTokenEvent(std::string token_text);

    void visit(EventVisitor& visitor) override;

    std::string token_text;
};
