#include "BlockMiniparser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/BeginWhileDeclEvent.h"
#include "parser/events/BeginIfDeclEvent.h"
#include "parser/events/BeginBlockDeclEvent.h"
#include "parser/events/EndBlockDeclEvent.h"
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
    return std::make_shared<BeginIfDeclEvent>(std::move(expression));
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
    return std::make_shared<BeginWhileDeclEvent>(std::move(expression));
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
    std::string result;
    for (auto token_type : {"INT", "IDENTIFIER", "SEMICOLON"}) {
        auto token = lexer.next_token_with_type(token_type);
        if (!token.valid()) {
            return nullptr;
        }
        if (token.type == "IDENTIFIER") {
            result = token.text;
        }
    }
    state.drop();
    return std::make_shared<VarDeclEvent>(result);
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
        return std::make_shared<BeginBlockDeclEvent>();
    }
    return nullptr;
}

std::shared_ptr<ASTEvent> BlockMiniparser::end_block_ast_event() {
    return std::make_shared<EndBlockDeclEvent>();
}
