#pragma once

#include "ASTEvent.h"

struct BeginBlockStmtEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
