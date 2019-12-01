#include "Parser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/EOFEvent.h"
#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/BeginMainDeclEvent.h"
#include "parser/events/ParseErrorEvent.h"
#include "parser/events/EndMainDeclEvent.h"
#include "parser/events/VarDeclEvent.h"
#include "parser/events/ExprStmtEvent.h"
#include "expression_parser/ExpressionParser.h"

class Stage {
public:
    virtual ~Stage() = default;
    bool completed() const {
        return _completed;
    }

    virtual std::unique_ptr<ASTEvent> try_eat(Lexer& lexer) = 0;

protected:
    std::unique_ptr<ASTEvent> eat_error(Lexer& lexer, Lexer::State& state) {
        state.revert();
        return std::make_unique<ParseErrorEvent>(lexer.next_token());
    }

    Token eat_token(const std::string& token_type, Lexer& lexer) {
        auto token = lexer.next_token();
        if (token.type == token_type) {
            return token;
        } else {
            return {};
        }
    }

    bool _completed = false;
};

class BeginMainStage : public Stage {
public:
    std::unique_ptr<ASTEvent> try_eat(Lexer& lexer) override {
        auto state = lexer.get_state();
        for (auto token_type : {"INT", "IDENTIFIER", "LPAR", "RPAR", "LBRACE"}) {
            auto token = eat_token(token_type, lexer);
            if (!token.valid() || (token.type == "IDENTIFIER" && token.text != "main")) {
                return nullptr;
            }
        }
        state.drop();
        _completed = true;
        return std::make_unique<BeginMainDeclEvent>();
    }
};

class StmtListStage : public Stage {
public:
    std::unique_ptr<ASTEvent> try_eat(Lexer& lexer) override {
        if (auto event = try_eat_return(lexer)) {
            return event;
        }

        if (auto event = try_eat_expr_stmt(lexer)) {
            return event;
        }

        if (auto event = try_eat_var_decl(lexer)) {
            return event;
        }

        _completed = true;
        return nullptr;
    }

private:
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
};

class EndMainStage : public Stage {
public:
    std::unique_ptr<ASTEvent> try_eat(Lexer& lexer) override {
        auto state = lexer.get_state();
        auto token = eat_token("RBRACE", lexer);
        if (!token.valid()) {
            return eat_error(lexer, state);
        }
        state.drop();
        _completed = true;
        return std::make_unique<EndMainDeclEvent>();
    }
};

Parser::Parser(Lexer& lexer) : _lexer(lexer) {
    _stages.push_back(std::make_unique<BeginMainStage>());
    _stages.push_back(std::make_unique<StmtListStage>());
    _stages.push_back(std::make_unique<EndMainStage>());
}

Parser::~Parser() = default;

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
    std::unique_ptr<ASTEvent> event = nullptr;
    while (!event && _current_stage < _stages.size()) {
        const auto& stage = _stages[_current_stage];
        event = stage->try_eat(_lexer);
        if (stage->completed()) {
            ++_current_stage;
        }
    }
    if (event) {
        return event;
    }

    auto token = _lexer.next_token();
    return std::make_unique<UnknownTokenTypeEvent>(token.type);
}
