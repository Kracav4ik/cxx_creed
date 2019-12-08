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
    std::unique_ptr<ASTEvent> try_eat_begin_main();

    Lexer& _lexer;
    std::unique_ptr<Miniparser> _miniparser;
};
