#pragma once

struct UnknownTokenEvent;
struct UnknownTokenTypeEvent;
struct EOFEvent;

class EventVisitor {
public:
    virtual ~EventVisitor() = default;

    virtual void visitUnknownToken(UnknownTokenEvent& event) {}
    virtual void visitUnknownTokenType(UnknownTokenTypeEvent& event) {}
    virtual void visitEOF(EOFEvent& event) {}
};
