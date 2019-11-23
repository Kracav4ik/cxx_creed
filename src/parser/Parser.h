#pragma once

#include "dlc/ParserDLC.h"
#include "dlc/WithDLC.h"

#include <memory>

struct ASTEvent;
class Lexer;
class Stage;

class Parser : public WithDLC<ParserDLC>  {
public:
    explicit Parser(Lexer& lexer);
    ~Parser();

    std::unique_ptr<ASTEvent> next_event();

private:
    Lexer& _lexer;
    std::vector<std::unique_ptr<Stage>> _stages;
    size_t _current_stage = 0;
};
