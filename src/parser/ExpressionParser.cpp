#include "ExpressionParser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"
#include "parser/ast/BinaryOpNode.h"
#include "parser/ast/UnaryOpNode.h"
#include "parser/ast/IntegerNode.h"

#include <algorithm>
#include <utility>
#include <cassert>

Priority ExpressionParserDLC::getPriority() const {
    return _priority;
}

ExpressionParserDLC::ExpressionParserDLC(Priority priority) : _priority(priority) {}

struct TokenList {
    explicit TokenList(std::vector<std::string> token_types) : token_types(std::move(token_types)) {}

    bool has_token_type(const std::string& token_type) const {
        return std::find(token_types.begin(), token_types.end(), token_type) != token_types.end();
    }

    std::vector<std::string> token_types;
};

ASTNodePtr try_binary_op(ExpressionParser& expression_parser, Lexer& lexer, const TokenList& token_types, Priority priority) {
    auto first_operand = expression_parser.try_next_priority(lexer, priority);
    if (!first_operand) {
        return nullptr;
    }

    while (true) {
        auto state = lexer.get_state();
        auto token = lexer.next_token();
        if (!token.valid() || !token_types.has_token_type(token.type)) {
            break;
        }

        auto second_operand = expression_parser.try_next_priority(lexer, priority);
        if (!second_operand) {
            break;
        }

        first_operand = std::make_unique<BinaryOpNode>(token.text, std::move(first_operand), std::move(second_operand));
        state.drop();
    }
    return first_operand;
}

ASTNodePtr try_unary_op(ExpressionParser& expression_parser, Lexer& lexer, const TokenList& token_types, Priority priority) {
    auto state = lexer.get_state();
    auto token = lexer.next_token();
    if (token.valid() && token_types.has_token_type(token.type)) {
        auto expression = expression_parser.try_same_priority(lexer, priority);
        if (!expression) {
            return nullptr;
        }
        state.drop();
        return std::make_unique<UnaryOpNode>(token.text, std::move(expression));
    } else {
        state.revert();
        return expression_parser.try_next_priority(lexer, priority);
    }
}

class BinaryOpParser : public ExpressionParserDLC {
public:
    BinaryOpParser(Priority priority, TokenList token_types) : ExpressionParserDLC(priority), _token_types(std::move(token_types)) {}

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expressionParser) override {
        return try_binary_op(expressionParser, lexer, _token_types, getPriority());
    }

private:
    TokenList _token_types;
};

class UnaryOpParser : public ExpressionParserDLC {
public:
    UnaryOpParser(Priority priority, TokenList token_types) : ExpressionParserDLC(priority), _token_types(std::move(token_types)) {}

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expressionParser) override {
        return try_unary_op(expressionParser, lexer, _token_types, getPriority());
    }

private:
    TokenList _token_types;
};

class ParensParser : public ExpressionParserDLC {
public:
    explicit ParensParser(Priority priority) : ExpressionParserDLC(priority) {}

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expressionParser) override {
        auto state = lexer.get_state();
        auto token = lexer.next_token();
        if (token.valid()) {
            if (token.type == "LPAR") {
                auto expression = expressionParser.try_expression(lexer);
                if (!expression) {
                    return nullptr;
                }
                token = lexer.next_token();
                if (token.valid() && token.type == "RPAR") {
                    state.drop();
                    return expression;
                }
            }
        }
        return nullptr;
    }
};

class IntegerParser : public ExpressionParserDLC {
public:
    explicit IntegerParser(Priority priority) : ExpressionParserDLC(priority) {}

    ASTNodePtr try_parse(Lexer& lexer, ExpressionParser& expressionParser) override {
        auto state = lexer.get_state();
        auto token = lexer.next_token();
        if (token.valid()) {
            if (token.type == "INTEGER") {
                state.drop();
                return std::make_unique<IntegerNode>(std::stoi(token.text));
            }
        }
        return nullptr;
    }
};

ExpressionParser::ExpressionParser() {
    add_dlc(std::make_shared<BinaryOpParser>(Priority::INCLUSIVE_OR_EXPRESSION, TokenList({"BITOR"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::EXCLUSIVE_OR_EXPRESSION, TokenList({"XOR"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::AND_EXPRESSION, TokenList({"BITAND"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::SHIFT_EXPRESSION, TokenList({"LSHIFT", "RSHIFT"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::ADDITIVE_EXPRESSION, TokenList({"ADD", "SUB"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::MULTIPLICATIVE_EXPRESSION, TokenList({"MUL", "DIV", "MOD"})));
    add_dlc(std::make_shared<UnaryOpParser>(Priority::UNARY_EXPRESSION, TokenList({"ADD", "SUB", "COMPL"})));
    add_dlc(std::make_shared<IntegerParser>(Priority::PRIMARY_EXPRESSION));
    add_dlc(std::make_shared<ParensParser>(Priority::PRIMARY_EXPRESSION));
}

ASTNodePtr ExpressionParser::try_expression(Lexer& lexer) {
    return try_parsers(lexer, _dlc_map.begin());
}

ASTNodePtr ExpressionParser::try_next_priority(Lexer& lexer, Priority priority) {
    return try_parsers(lexer, _dlc_map.upper_bound(priority));
}

ASTNodePtr ExpressionParser::try_same_priority(Lexer& lexer, Priority priority) {
    return try_parsers(lexer, _dlc_map.find(priority));
}

void ExpressionParser::add_dlc(std::shared_ptr<DLC> dlc) {
    if (std::dynamic_pointer_cast<BinaryOpParser>(dlc)) {
        // TODO: bug: multiple BinaryOpParser object with the same priority don't work
        assert(_dlc_map.count(dlc->getPriority()) == 0);
    }
    _dlc_map[dlc->getPriority()].push_back(std::move(dlc));
}

ASTNodePtr ExpressionParser::try_parsers(Lexer& lexer, DlcMap::const_iterator parsers_it) {
    if (parsers_it == _dlc_map.end()) {
        return nullptr;
    }
    for (const auto& dlc : parsers_it->second) {
        if (auto result = dlc->try_parse(lexer, *this)) {
            return result;
        }
    }
    return nullptr;
}
