#include "Parser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/EOFEvent.h"
#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/BeginMainDeclEvent.h"
#include "parser/events/EndMainDeclEvent.h"
#include "parser/events/VarDeclEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "parser/events/EndBlockDeclEvent.h"
#include "parser/events/BeginBlockDeclEvent.h"
#include "expression_parser/ExpressionParser.h"

Token eat_token(const std::string& token_type, Lexer& lexer) {
    auto token = lexer.next_token();
    if (token.type == token_type) {
        return token;
    } else {
        return {};
    }
}

class Miniparser {
public:
    bool completed() const {
        return _completed;
    }

    virtual std::unique_ptr<ASTEvent> try_next_event(Lexer& lexer) = 0;

protected:
    std::unique_ptr<Miniparser> _child;
    bool _completed = false;
};

class BlockMiniparser : public Miniparser {
public:
    std::unique_ptr<ASTEvent> try_next_event(Lexer& lexer) override {
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
        if (auto event = try_eat_self_end_block(lexer)) {
            return event;
        }
        return nullptr;
    }

protected:
    virtual std::unique_ptr<ASTEvent> try_eat_self_end_block(Lexer& lexer) {
        auto state = lexer.get_state();
        auto token = eat_token("RBRACE", lexer);
        if (token.valid()) {
            state.drop();
            _completed = true;
            return std::make_unique<EndBlockDeclEvent>();
        }
        return nullptr;
    }

private:
    std::unique_ptr<ASTEvent> try_eat_stmt_events(Lexer& lexer) {
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

    std::unique_ptr<ASTEvent> try_eat_return(Lexer& lexer) {
        auto state = lexer.get_state();

        if (!eat_token("RETURN", lexer).valid()) {
            return nullptr;
        }

        ExpressionParser expression_parser;
        auto expression = expression_parser.try_expression(lexer);
        if (!expression) {
            return nullptr;
        }

        if (!eat_token("SEMICOLON", lexer).valid()) {
            return nullptr;
        }
        state.drop();
        return std::make_unique<ReturnStmtEvent>(std::move(expression));
    }

    std::unique_ptr<ASTEvent> try_eat_var_decl(Lexer& lexer) {
        auto state = lexer.get_state();
        std::string result;
        for (auto token_type : {"INT", "IDENTIFIER", "SEMICOLON"}) {
            auto token = eat_token(token_type, lexer);
            if (!token.valid()) {
                return nullptr;
            }
            if (token.type == "IDENTIFIER") {
                result = token.text;
            }
        }
        state.drop();
        return std::make_unique<VarDeclEvent>(result);
    }

    std::unique_ptr<ASTEvent> try_eat_expr_stmt(Lexer& lexer) {
        auto state = lexer.get_state();

        ExpressionParser expression_parser;
        auto expression = expression_parser.try_expression(lexer);
        if (!expression) {
            return nullptr;
        }

        if (!eat_token("SEMICOLON", lexer).valid()) {
            return nullptr;
        }
        state.drop();
        return std::make_unique<ExprStmtEvent>(std::move(expression));
    }

    std::unique_ptr<ASTEvent> try_eat_begin_block(Lexer& lexer) {
        auto state = lexer.get_state();
        auto token = eat_token("LBRACE", lexer);
        if (token.valid()) {
            state.drop();
            _child = std::make_unique<BlockMiniparser>();
            return std::make_unique<BeginBlockDeclEvent>();
        }
        return nullptr;
    }
};


class MainMiniparser : public BlockMiniparser {
protected:
    std::unique_ptr<ASTEvent> try_eat_self_end_block(Lexer& lexer) override {
        auto state = lexer.get_state();
        auto token = eat_token("RBRACE", lexer);
        if (token.valid()) {
            state.drop();
            _completed = true;
            return std::make_unique<EndMainDeclEvent>();
        }
        return nullptr;
    }
};

Parser::Parser(Lexer& lexer) : _lexer(lexer), _miniparser(nullptr) {
}

Parser::~Parser() = default;

std::unique_ptr<ASTEvent> Parser::try_eat_begin_main() {
    auto state = _lexer.get_state();
    for (auto token_type : {"INT", "IDENTIFIER", "LPAR", "RPAR", "LBRACE"}) {
        auto token = eat_token(token_type, _lexer);
        if (!token.valid() || (token.type == "IDENTIFIER" && token.text != "main")) {
            return nullptr;
        }
    }
    state.drop();
    return std::make_unique<BeginMainDeclEvent>();
}

std::unique_ptr<ASTEvent> Parser::next_event() {
    {
        auto state = _lexer.get_state();
        auto token = _lexer.next_token();
        if (token.type == "UNKNOWN") {
            state.drop();
            return std::make_unique<UnknownTokenEvent>(token.text);
        }
        if (token.type == "EOF") {
            state.drop();
            return std::make_unique<EOFEvent>();
        }
    }

    if (!_miniparser) {
        if (auto event = try_eat_begin_main()) {
            _miniparser = std::make_unique<MainMiniparser>();
            return event;
        }
    } else {
        if (auto event = _miniparser->try_next_event(_lexer)) {
            if (_miniparser->completed()) {
                _miniparser.reset();
            }
            return event;
        }
    }

    auto token = _lexer.next_token();
    return std::make_unique<UnknownTokenTypeEvent>(token.type);
}
