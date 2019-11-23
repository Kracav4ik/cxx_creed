#pragma once

#include "ASTEvent.h"
#include "lexer/Token.h"

struct ParseErrorEvent : public ASTEvent {
    explicit ParseErrorEvent(Token token);

    void visit(EventVisitor& visitor) override;

    Token token;
};
