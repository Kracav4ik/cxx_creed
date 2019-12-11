#pragma once

#include <memory>

struct ASTEvent;
class ParserBase {
public:
    virtual std::shared_ptr<ASTEvent> next_event() = 0;
};
