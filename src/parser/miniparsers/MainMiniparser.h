#pragma once

#include "BlockMiniparser.h"

class MainMiniparser : public BlockMiniparser {
public:
    std::shared_ptr<ASTEvent> try_next_event(Lexer& lexer) override;

private:
    std::shared_ptr<ASTEvent> end_block_ast_event() override;
    std::shared_ptr<ASTEvent> try_eat_begin_main(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_include(Lexer& lexer);
    bool _main_begin = false;
};
