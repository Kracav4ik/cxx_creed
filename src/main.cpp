#include "util.h"

#include <iostream>
#include <memory>
#include <vector>

struct Token {
    std::string type;
    std::string value;
};

struct UnknownTokenEvent;
struct UnknownTokenTypeEvent;
struct EOFEvent;

class EventVisitor {
public:
    virtual ~EventVisitor() = default;

    virtual void visitUnknownToken(UnknownTokenEvent& event) {}
    virtual void visitUnknownTokenType(UnknownTokenTypeEvent& event) {}
    virtual void visitEOF(EOFEvent& event) {}
};

struct ASTEvent {
    virtual ~ASTEvent() = default;
    virtual void visit(EventVisitor& visitor) = 0;
};

struct UnknownTokenEvent : public ASTEvent {
    explicit UnknownTokenEvent(std::string token_text) : token_text(std::move(token_text)) {}

    void visit(EventVisitor& visitor) override {
        visitor.visitUnknownToken(*this);
    }

    std::string token_text;
};

struct UnknownTokenTypeEvent : public ASTEvent {
    explicit UnknownTokenTypeEvent(std::string token_type) : token_type(std::move(token_type)) {}

    void visit(EventVisitor& visitor) override {
        visitor.visitUnknownTokenType(*this);
    }

    std::string token_type;
};

struct EOFEvent : public ASTEvent {
    void visit(EventVisitor& visitor) override {
        visitor.visitEOF(*this);
    }
};


template <typename T>
class WithDLC {
public:
    using DLC = T;

    void add_dlc(std::shared_ptr<DLC> dlc) {
        _dlcList.push_back(std::move(dlc));
    }

protected:
    std::vector<std::shared_ptr<DLC>> _dlcList;
};

class LexerDLC {
public:
    virtual ~LexerDLC() = default;
};


class Lexer : public WithDLC<LexerDLC> {
public:
    void set_text(std::string text) {
        _text = std::move(text);
        _pos = 0;
    }

    Token next_token() {
        if (_pos == _text.size()) {
            return {"EOF", ""};
        }
        Token result{"UNKNOWN", _text.substr(_pos, 1)};
        ++_pos;
        return result;
    }

public:
    std::string _text;
    size_t _pos = 0;
};


class ParserDLC {
public:
    virtual ~ParserDLC() = default;
};

class Parser : public WithDLC<ParserDLC>  {
public:
    explicit Parser(Lexer& lexer) : _lexer(lexer) {}

    std::unique_ptr<ASTEvent> next_event() {
        auto token = _lexer.next_token();
        if (token.type == "UNKNOWN") {
            return std::make_unique<UnknownTokenEvent>(token.value);
        }
        if (token.type == "EOF") {
            return std::make_unique<EOFEvent>();
        }
        return std::make_unique<UnknownTokenTypeEvent>(token.type);
    }

private:
    Lexer& _lexer;
};


class InterpreterDLC {
public:
    virtual ~InterpreterDLC() = default;
};


class Interpreter : public WithDLC<InterpreterDLC>, EventVisitor {
public:
    explicit Interpreter(Parser& parser) : _parser(parser) {}

    void run() {
        _isRunning = true;
        while (_isRunning) {
            auto event = _parser.next_event();
            event->visit(*this);
        }
    }

private:
    void visitUnknownToken(UnknownTokenEvent& event) override {
        std::cerr << "unknown token: `" << event.token_text << "`" << std::endl;
    }

    void visitUnknownTokenType(UnknownTokenTypeEvent& event) override {
        std::cerr << "unknown token type: " << event.token_type << std::endl;
    }

    void visitEOF(EOFEvent& event) override {
        _isRunning = false;
    }

    bool _isRunning = false;
    Parser& _parser;
};


class ExpansionPack {
public:
    void install(Lexer& lexer, Parser& parser, Interpreter& interpreter) {

    }
};




int main() {
    Lexer lexer;
    Parser parser(lexer);
    Interpreter interpreter(parser);

    ExpansionPack pack;
    pack.install(lexer, parser, interpreter);

    std::string text = read_file("../src/main.cpp");
    std::cout << "----------\n" << text << "\n----------" << std::endl;

    lexer.set_text(text);
    interpreter.run();

    return 0;
}
