#pragma once

#include "ParserBase.h"
#include "dlc/ParserDLC.h"
#include "dlc/WithDLC.h"

class Lexer;
class Miniparser;
class Parser : public ParserBase, public WithDLC<ParserDLC> {
public:
    explicit Parser(Lexer& lexer);
    ~Parser();

    std::shared_ptr<ASTEvent> next_event() override;

private:
    Lexer& _lexer;
    std::unique_ptr<Miniparser> _miniparser;
};
