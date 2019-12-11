#pragma once

#include "ASTEvent.h"

struct EndWhileStmtEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
