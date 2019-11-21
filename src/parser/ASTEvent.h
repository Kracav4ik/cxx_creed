#pragma once

class EventVisitor;

struct ASTEvent {
    virtual ~ASTEvent() = default;
    virtual void visit(EventVisitor& visitor) = 0;
};
