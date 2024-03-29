#include "BlockMiniparser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/BeginWhileStmtEvent.h"
#include "parser/events/BeginIfStmtEvent.h"
#include "parser/events/BeginBlockStmtEvent.h"
#include "parser/events/EndBlockStmtEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/VarDeclEvent.h"
#include "expression_parser/ExpressionParser.h"
#include "IfMiniparser.h"
#include "WhileMiniparser.h"


std::shared_ptr<ASTEvent> BlockMiniparser::try_next_event(Lexer& lexer) {
    if (_child) {
        auto event = _child->try_next_event(lexer);
        if (_child->completed()) {
            _child.reset();
        }
        return event;
    }
    if (auto event = try_eat_stmt_events(lexer)) {
        return event;
    }
    if (auto event = try_eat_begin_block(lexer)) {
        return event;
    }
    if (auto event = try_eat_begin_if(lexer)) {
        return event;
    }
    if (auto event = try_eat_begin_while(lexer)) {
        return event;
    }
    if (auto event = try_eat_self_end_block(lexer)) {
        return event;
    }
    return nullptr;
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_self_end_block(Lexer& lexer) {
    auto state = lexer.get_state();
    if (auto token = lexer.next_token_with_type("RBRACE")) {
        state.drop();
        _completed = true;
        return end_block_ast_event();
    }
    return nullptr;
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_stmt_events(Lexer& lexer) {
    if (auto event = try_eat_return(lexer)) {
        return event;
    }

    if (auto event = try_eat_expr_stmt(lexer)) {
        return event;
    }

    if (auto event = try_eat_var_decl(lexer)) {
        return event;
    }
    return nullptr;
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_begin_if(Lexer& lexer) {
    auto state = lexer.get_state();

    if (!lexer.next_token_with_type("IF").valid()) {
        return nullptr;
    }

    if (!lexer.next_token_with_type("LPAR").valid()) {
        return nullptr;
    }

    ExpressionParser expression_parser;
    auto expression = expression_parser.try_expression(lexer);
    if (!expression) {
        return nullptr;
    }

    if (!lexer.next_token_with_type("RPAR").valid()) {
        return nullptr;
    }
    if (!lexer.next_token_with_type("LBRACE").valid()) {
        return nullptr;
    }

    state.drop();
    _child = std::make_unique<IfMiniparser>();
    return std::make_shared<BeginIfStmtEvent>(std::move(expression));
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_begin_while(Lexer& lexer) {
    auto state = lexer.get_state();

    if (!lexer.next_token_with_type("WHILE").valid()) {
        return nullptr;
    }

    if (!lexer.next_token_with_type("LPAR").valid()) {
        return nullptr;
    }

    ExpressionParser expression_parser;
    auto expression = expression_parser.try_expression(lexer);
    if (!expression) {
        return nullptr;
    }

    if (!lexer.next_token_with_type("RPAR").valid()) {
        return nullptr;
    }
    if (!lexer.next_token_with_type("LBRACE").valid()) {
        return nullptr;
    }

    state.drop();
    _child = std::make_unique<WhileMiniparser>();
    return std::make_shared<BeginWhileStmtEvent>(std::move(expression));
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_return(Lexer& lexer) {
    auto state = lexer.get_state();

    if (!lexer.next_token_with_type("RETURN").valid()) {
        return nullptr;
    }

    ExpressionParser expression_parser;
    auto expression = expression_parser.try_expression(lexer);
    if (!expression) {
        return nullptr;
    }

    if (!lexer.next_token_with_type("SEMICOLON").valid()) {
        return nullptr;
    }
    state.drop();
    return std::make_shared<ReturnStmtEvent>(std::move(expression));
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_var_decl(Lexer& lexer) {
    auto state = lexer.get_state();
    std::string type_name;
    std::string var_name;
    if (auto token = try_eat_typename(lexer)) {
        if (!token.valid()) {
            return nullptr;
        }
        type_name = token.text;
    } else {
        return nullptr;
    }
    if (auto token = lexer.next_token_with_type("IDENTIFIER")) {
        if (!token.valid()) {
            return nullptr;
        }
        var_name = token.text;
    } else {
        return nullptr;
    }
    if (!lexer.next_token_with_type("SEMICOLON").valid()) {
        return nullptr;
    }
    state.drop();
    return std::make_shared<VarDeclEvent>(type_name, var_name);
}

Token BlockMiniparser::try_eat_typename(Lexer& lexer) const {
    {
        auto state = lexer.get_state();
        if (auto token = lexer.next_token_with_type("INT")) {
            state.drop();
            return token;
        }
    }
    {
        auto state = lexer.get_state();
        if(auto token = lexer.next_token_with_type("IDENTIFIER")) {
            state.drop();
            return token;
        }
    }
    return {};
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_expr_stmt(Lexer& lexer) {
    auto state = lexer.get_state();

    ExpressionParser expression_parser;
    auto expression = expression_parser.try_expression(lexer);
    if (!expression) {
        return nullptr;
    }

    if (!lexer.next_token_with_type("SEMICOLON").valid()) {
        return nullptr;
    }
    state.drop();
    return std::make_shared<ExprStmtEvent>(std::move(expression));
}

std::shared_ptr<ASTEvent> BlockMiniparser::try_eat_begin_block(Lexer& lexer) {
    auto state = lexer.get_state();
    if (auto token = lexer.next_token_with_type("LBRACE")) {
        state.drop();
        _child = std::make_unique<BlockMiniparser>();
        return std::make_shared<BeginBlockStmtEvent>();
    }
    return nullptr;
}

std::shared_ptr<ASTEvent> BlockMiniparser::end_block_ast_event() {
    return std::make_shared<EndBlockStmtEvent>();
}
