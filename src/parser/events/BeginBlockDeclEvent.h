#pragma once

#include "ASTEvent.h"

struct BeginBlockDeclEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
