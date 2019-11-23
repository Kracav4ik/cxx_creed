#pragma once

#include "ASTEvent.h"

struct ReturnStmtEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
