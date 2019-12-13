#include "ExpressionParser.h"

#include "dlc/expression_parsers/BinaryOpParser.h"
#include "dlc/expression_parsers/IntegerParser.h"
#include "dlc/expression_parsers/StringParser.h"
#include "dlc/expression_parsers/ParensParser.h"
#include "dlc/expression_parsers/UnaryOpParser.h"
#include "dlc/expression_parsers/AssignmentParser.h"
#include "dlc/expression_parsers/VariableParser.h"

#include <cassert>

ExpressionParser::ExpressionParser() {
    add_dlc(std::make_shared<AssignmentParser>(Priority::ASSIGNMENT_EXPRESSION));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::LOGICAL_OR_EXPRESSION, TokenList({"OR"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::LOGICAL_AND_EXPRESSION, TokenList({"AND"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::INCLUSIVE_OR_EXPRESSION, TokenList({"BITOR"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::EXCLUSIVE_OR_EXPRESSION, TokenList({"XOR"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::AND_EXPRESSION, TokenList({"BITAND"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::EQUALITY_EXPRESSION, TokenList({"EQ", "NOTEQ"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::RELATIONAL_EXPRESSION, TokenList({"LT", "LTEQ", "GT", "GTEQ"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::SHIFT_EXPRESSION, TokenList({"LSHIFT", "RSHIFT"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::ADDITIVE_EXPRESSION, TokenList({"ADD", "SUB"})));
    add_dlc(std::make_shared<BinaryOpParser>(Priority::MULTIPLICATIVE_EXPRESSION, TokenList({"MUL", "DIV", "MOD"})));
    add_dlc(std::make_shared<UnaryOpParser>(Priority::UNARY_EXPRESSION, TokenList({"ADD", "SUB", "COMPL", "NOT"})));
    add_dlc(std::make_shared<IntegerParser>(Priority::PRIMARY_EXPRESSION));
    add_dlc(std::make_shared<StringParser>(Priority::PRIMARY_EXPRESSION));
    add_dlc(std::make_shared<ParensParser>(Priority::PRIMARY_EXPRESSION));
    add_dlc(std::make_shared<VariableParser>(Priority::PRIMARY_EXPRESSION));
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
