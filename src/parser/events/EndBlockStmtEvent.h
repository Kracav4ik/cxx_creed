#pragma once

#include "ASTEvent.h"

struct EndBlockStmtEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
