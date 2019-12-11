#pragma once

#include <memory>

struct ASTEvent;
class Lexer;

class Miniparser {
public:
    bool completed() const;

    virtual std::shared_ptr<ASTEvent> try_next_event(Lexer& lexer) = 0;

protected:
    std::unique_ptr<Miniparser> _child;
    bool _completed = false;
};
