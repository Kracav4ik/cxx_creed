#pragma once

#include "ASTEvent.h"

struct EOFEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
