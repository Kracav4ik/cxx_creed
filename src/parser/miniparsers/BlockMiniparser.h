#pragma once

#include "Miniparser.h"

class BlockMiniparser : public Miniparser {
public:
    std::unique_ptr<ASTEvent> try_next_event(Lexer& lexer) override;

protected:
    virtual std::unique_ptr<ASTEvent> end_block_ast_event();

private:
    std::unique_ptr<ASTEvent> try_eat_self_end_block(Lexer& lexer);
    std::unique_ptr<ASTEvent> try_eat_stmt_events(Lexer& lexer);
    std::unique_ptr<ASTEvent> try_eat_begin_if(Lexer& lexer);
    std::unique_ptr<ASTEvent> try_eat_return(Lexer& lexer);
    std::unique_ptr<ASTEvent> try_eat_var_decl(Lexer& lexer);
    std::unique_ptr<ASTEvent> try_eat_expr_stmt(Lexer& lexer);
    std::unique_ptr<ASTEvent> try_eat_begin_block(Lexer& lexer);
};
