#pragma once

#include "ASTEvent.h"

struct EndIfDeclEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
