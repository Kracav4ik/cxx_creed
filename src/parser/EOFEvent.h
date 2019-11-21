#pragma once

#include "parser/ASTEvent.h"

struct EOFEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
