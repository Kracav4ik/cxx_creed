#pragma once

#include "ASTEvent.h"

struct EndWhileDeclEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override;
};
