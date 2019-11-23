#pragma once

#include "ASTEvent.h"

struct EndMainDeclEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
