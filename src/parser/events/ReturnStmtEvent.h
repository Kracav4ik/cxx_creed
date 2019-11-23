#pragma once

#include "ASTEvent.h"
#include <string>

struct ReturnStmtEvent : public ASTEvent {
    explicit ReturnStmtEvent(std::string value);
    void visit(EventVisitor& visitor) override;

    std::string value;
};
