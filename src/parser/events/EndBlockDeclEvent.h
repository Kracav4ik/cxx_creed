#pragma once

#include "ASTEvent.h"

struct EndBlockDeclEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
