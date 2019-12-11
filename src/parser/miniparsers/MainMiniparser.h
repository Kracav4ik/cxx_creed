#pragma once

#include "BlockMiniparser.h"

class MainMiniparser : public BlockMiniparser {
public:
    std::unique_ptr<ASTEvent> try_next_event(Lexer& lexer) override;

private:
    std::unique_ptr<ASTEvent> end_block_ast_event() override;
    std::unique_ptr<ASTEvent> try_eat_begin_main(Lexer& lexer);
    bool _main_begin = false;
};
