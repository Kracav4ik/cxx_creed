#pragma once

#include "Miniparser.h"

class BlockMiniparser : public Miniparser {
public:
    std::shared_ptr<ASTEvent> try_next_event(Lexer& lexer) override;

protected:
    virtual std::shared_ptr<ASTEvent> end_block_ast_event();

private:
    std::shared_ptr<ASTEvent> try_eat_self_end_block(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_stmt_events(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_begin_if(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_begin_while(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_return(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_var_decl(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_expr_stmt(Lexer& lexer);
    std::shared_ptr<ASTEvent> try_eat_begin_block(Lexer& lexer);
};
