#pragma once

#include "ASTEvent.h"

struct EndIfStmtEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
