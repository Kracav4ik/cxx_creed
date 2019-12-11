#pragma once

#include "dlc/ParserDLC.h"
#include "dlc/WithDLC.h"

#include <memory>

struct ASTEvent;
class Lexer;
class Miniparser;

class Parser : public WithDLC<ParserDLC>  {
public:
    explicit Parser(Lexer& lexer);
    ~Parser();

    std::unique_ptr<ASTEvent> next_event();

private:
    Lexer& _lexer;
    std::unique_ptr<Miniparser> _miniparser;
};
