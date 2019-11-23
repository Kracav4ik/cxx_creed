#include "Parser.h"

#include "parser/events/EOFEvent.h"
#include "parser/events/UnknownTokenEvent.h"
#include "parser/events/UnknownTokenTypeEvent.h"
#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/events/ReturnStmtEvent.h"
#include "parser/events/BeginMainDeclEvent.h"
#include "parser/events/ParseErrorEvent.h"
#include "parser/events/EndMainDeclEvent.h"
#include "parser/ast/IntegerNode.h"

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
        lexer.skip_whitespace();
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
                return eat_error(lexer, state);
            }
        }
        state.drop();
        _completed = true;
        return std::make_unique<BeginMainDeclEvent>();
    }
};

class ReturnStage : public Stage {
public:
    std::unique_ptr<ASTEvent> try_eat(Lexer& lexer) override {
        auto state = lexer.get_state();
        std::string value;
        for (auto token_type : {"RETURN", "INTEGER", "SEMICOLON"}) {
            auto token = eat_token(token_type, lexer);
            if (!token.valid()) {
                return eat_error(lexer, state);
            }
            if (token.type == "INTEGER") {
                value = token.text;
            }
        }
        state.drop();
        _completed = true;
        return std::make_unique<ReturnStmtEvent>(std::make_unique<IntegerNode>(std::stoi(value)));
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
    _stages.push_back(std::make_unique<ReturnStage>());
    _stages.push_back(std::make_unique<EndMainStage>());
}

Parser::~Parser() = default;

std::unique_ptr<ASTEvent> Parser::next_event() {
    _lexer.skip_whitespace();
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
    if (_current_stage < _stages.size()) {
        const auto& stage = _stages[_current_stage];
        auto event = stage->try_eat(_lexer);
        if (stage->completed()) {
            ++_current_stage;
        }
        return event;
    }

    auto token = _lexer.next_token();
    return std::make_unique<UnknownTokenTypeEvent>(token.type);
}
