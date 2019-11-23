#pragma once

#include "ASTEvent.h"

struct BeginMainDeclEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
