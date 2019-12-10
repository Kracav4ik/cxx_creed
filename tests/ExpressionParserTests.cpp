#include "gtest/gtest.h"

#include "helpers/ExpressionChecker.h"
#include "helpers/TestPrinter.h"

#include "dlc/expression_parsers/BinaryOpParser.h"
#include "dlc/expression_parsers/UnaryOpParser.h"
#include "expression_parser/ExpressionParser.h"

TEST(ExpressionParserTest, basics) {
    TestPrinter printer;
    EXPECT_EQ(ExpressionChecker("").str(), "");
    EXPECT_EQ(ExpressionChecker("1").str(), "[Integer 1]");
    EXPECT_EQ(ExpressionChecker("1 2").str(), "[Integer 1]");
    EXPECT_EQ(ExpressionChecker("1 ; 2").str(), "[Integer 1]");
    EXPECT_EQ(ExpressionChecker("1 $ 2").str(), "[Integer 1]");
}

TEST(ExpressionParserTest, arithmetics) {
    TestPrinter printer;
    EXPECT_EQ(ExpressionChecker("1 + 2").str(), "[BinaryOp [Integer 1] + [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 - 2").str(), "[BinaryOp [Integer 1] - [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 * 2").str(), "[BinaryOp [Integer 1] * [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 / 2").str(), "[BinaryOp [Integer 1] / [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 % 2").str(), "[BinaryOp [Integer 1] % [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 ^ 2").str(), "[BinaryOp [Integer 1] ^ [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 & 2").str(), "[BinaryOp [Integer 1] & [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 | 2").str(), "[BinaryOp [Integer 1] | [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 << 2").str(), "[BinaryOp [Integer 1] << [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 >> 2").str(), "[BinaryOp [Integer 1] >> [Integer 2]]");

    EXPECT_EQ(ExpressionChecker("1 + 2 - 3 + 4").str(), ""
            "[BinaryOp "
                "[BinaryOp "
                    "[BinaryOp "
                        "[Integer 1]"
                        " + "
                        "[Integer 2]"
                    "]"
                    " - "
                    "[Integer 3]"
                "]"
                " + "
                "[Integer 4]"
            "]"
    );
    EXPECT_EQ(ExpressionChecker("1 * 2 / 3 % 4").str(), (
            "[BinaryOp "
                "[BinaryOp "
                    "[BinaryOp "
                        "[Integer 1]"
                        " * "
                        "[Integer 2]"
                    "]"
                    " / "
                    "[Integer 3]"
                "]"
                " % "
                "[Integer 4]"
            "]"
    ));

    EXPECT_EQ(ExpressionChecker("1 - 20 * 300 + 100 / 10 + 5 % 2").str(), (
            "[BinaryOp "
                "[BinaryOp "
                    "[BinaryOp "
                        "[Integer 1]"
                        " - "
                        "[BinaryOp "
                            "[Integer 20]"
                            " * "
                            "[Integer 300]"
                        "]"
                    "]"
                    " + "
                    "[BinaryOp "
                        "[Integer 100]"
                        " / "
                        "[Integer 10]"
                    "]"
                "]"
                " + "
                "[BinaryOp "
                    "[Integer 5]"
                    " % "
                    "[Integer 2]"
                "]"
            "]"
    ));
}

TEST(ExpressionParserTest, parens) {
    TestPrinter printer;
    EXPECT_EQ(ExpressionChecker("()").str(), "");
    EXPECT_EQ(ExpressionChecker("(1)").str(), "[Integer 1]");
    EXPECT_EQ(ExpressionChecker("(((1)))").str(), "[Integer 1]");
    EXPECT_EQ(ExpressionChecker("(3 + 5)").str(), "[BinaryOp [Integer 3] + [Integer 5]]");
    EXPECT_EQ(ExpressionChecker("(3 * 5)").str(), "[BinaryOp [Integer 3] * [Integer 5]]");
    EXPECT_EQ(ExpressionChecker("(- 5)").str(), "[UnaryOp - [Integer 5]]");
    EXPECT_EQ(ExpressionChecker("2 * (3 + 5").str(), "[Integer 2]");
    EXPECT_EQ(ExpressionChecker("2 * (3 + 5)").str(), "[BinaryOp [Integer 2] * [BinaryOp [Integer 3] + [Integer 5]]]");
    EXPECT_EQ(ExpressionChecker("(1 - 2) * 3").str(), "[BinaryOp [BinaryOp [Integer 1] - [Integer 2]] * [Integer 3]]");
    EXPECT_EQ(ExpressionChecker("(1 - 2) * (3 + 5)").str(), "[BinaryOp [BinaryOp [Integer 1] - [Integer 2]] * [BinaryOp [Integer 3] + [Integer 5]]]");
}

TEST(ExpressionParserTest, variables) {
    TestPrinter printer;
    EXPECT_EQ(ExpressionChecker("x").str(), "[Variable x]");
    EXPECT_EQ(ExpressionChecker("x + y * z").str(), "[BinaryOp [Variable x] + [BinaryOp [Variable y] * [Variable z]]]");
    EXPECT_EQ(ExpressionChecker("5+e").str(), "[BinaryOp [Integer 5] + [Variable e]]");
}

TEST(ExpressionParserTest, assignment) {
    TestPrinter printer;
    EXPECT_EQ(ExpressionChecker("=").str(), "");
    EXPECT_EQ(ExpressionChecker("1 = 2").str(), "[AssignmentOp [Integer 1] = [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("a = b").str(), "[AssignmentOp [Variable a] = [Variable b]]");
    EXPECT_EQ(ExpressionChecker("a = b = c = d").str(), "[AssignmentOp [Variable a] = [AssignmentOp [Variable b] = [AssignmentOp [Variable c] = [Variable d]]]]");
}

TEST(ExpressionParserTest, unary_op) {
    TestPrinter printer;
    EXPECT_EQ(ExpressionChecker("+").str(), "");
    EXPECT_EQ(ExpressionChecker("+1").str(), "[UnaryOp + [Integer 1]]");
    EXPECT_EQ(ExpressionChecker("-1").str(), "[UnaryOp - [Integer 1]]");
    EXPECT_EQ(ExpressionChecker("~1").str(), "[UnaryOp ~ [Integer 1]]");
    EXPECT_EQ(ExpressionChecker("!1").str(), "[UnaryOp ! [Integer 1]]");
    EXPECT_EQ(ExpressionChecker("+ ~ - ! + - 1").str(), "[UnaryOp + [UnaryOp ~ [UnaryOp - [UnaryOp ! [UnaryOp + [UnaryOp - [Integer 1]]]]]]]");
    EXPECT_EQ(ExpressionChecker("3 * ~ - ! (+ 1)").str(),"[BinaryOp [Integer 3] * [UnaryOp ~ [UnaryOp - [UnaryOp ! [UnaryOp + [Integer 1]]]]]]");
}

TEST(ExpressionParserTest, binary_priority) {
    TestPrinter printer;
    EXPECT_EQ(ExpressionChecker("1 = 2 || 3 = 4").str(),
              "[AssignmentOp [Integer 1] = [AssignmentOp [BinaryOp [Integer 2] || [Integer 3]] = [Integer 4]]]");
    EXPECT_EQ(ExpressionChecker("1 || 2 && 3 || 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] || [BinaryOp [Integer 2] && [Integer 3]]] || [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 && 2 | 3 && 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] && [BinaryOp [Integer 2] | [Integer 3]]] && [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 | 2 ^ 3 | 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] | [BinaryOp [Integer 2] ^ [Integer 3]]] | [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 ^ 2 & 3 ^ 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] ^ [BinaryOp [Integer 2] & [Integer 3]]] ^ [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 & 2 == 3 & 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] & [BinaryOp [Integer 2] == [Integer 3]]] & [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 & 2 != 3 & 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] & [BinaryOp [Integer 2] != [Integer 3]]] & [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 == 2 < 3 != 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] == [BinaryOp [Integer 2] < [Integer 3]]] != [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 == 2 <= 3 != 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] == [BinaryOp [Integer 2] <= [Integer 3]]] != [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 == 2 > 3 != 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] == [BinaryOp [Integer 2] > [Integer 3]]] != [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 == 2 >= 3 != 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] == [BinaryOp [Integer 2] >= [Integer 3]]] != [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 < 2 << 3 > 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] < [BinaryOp [Integer 2] << [Integer 3]]] > [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 < 2 >> 3 > 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] < [BinaryOp [Integer 2] >> [Integer 3]]] > [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 <= 2 << 3 >= 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] <= [BinaryOp [Integer 2] << [Integer 3]]] >= [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 <= 2 >> 3 >= 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] <= [BinaryOp [Integer 2] >> [Integer 3]]] >= [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 << 2 + 3 >> 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] << [BinaryOp [Integer 2] + [Integer 3]]] >> [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 << 2 - 3 >> 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] << [BinaryOp [Integer 2] - [Integer 3]]] >> [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 + 2 * 3 - 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] + [BinaryOp [Integer 2] * [Integer 3]]] - [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 + 2 / 3 - 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] + [BinaryOp [Integer 2] / [Integer 3]]] - [Integer 4]]");
    EXPECT_EQ(ExpressionChecker("1 + 2 % 3 - 4").str(),
              "[BinaryOp [BinaryOp [Integer 1] + [BinaryOp [Integer 2] % [Integer 3]]] - [Integer 4]]");
}

TEST(ExpressionParserTest, check_errors) {
    EXPECT_EQ(ExpressionChecker("2000000000 + 2000000000").str_messages(),
              "Integer overflow\n");
    EXPECT_EQ(ExpressionChecker("-2000000000 - 2000000000").str_messages(),
              "Integer underflow\n");
    EXPECT_EQ(ExpressionChecker("2000000000 * 2000000000").str_messages(),
              "Integer overflow\n");
    EXPECT_EQ(ExpressionChecker("-2000000000 * 2000000000").str_messages(),
              "Integer underflow\n");
    EXPECT_EQ(ExpressionChecker("(-2147483647 - 1) / -1").str_messages(),
              "Integer overflow\n");
    EXPECT_EQ(ExpressionChecker("2183648 / 0").str_messages(),
              "Integer division by zero\n");
    EXPECT_EQ(ExpressionChecker("-2183648 % 0").str_messages(),
              "Remainder of integer division by zero\n");
    EXPECT_EQ(ExpressionChecker("2147483648").value(),
              -2147483648);
    EXPECT_EQ(ExpressionChecker("-2147483648").value(),
              -2147483648);
    EXPECT_EQ(ExpressionChecker("(-2147483648) * -1").value(),
              -2147483648);
    EXPECT_EQ(ExpressionChecker("2147483647 + 1").value(),
              -2147483648);
}

TEST(ExpressionParserDeathTest, unknown_op) {
    ExpressionParser expression_parser;
    expression_parser.add_dlc(std::make_shared<BinaryOpParser>(Priority::CONDITIONAL_EXPRESSION, TokenList({"COMPL"})));
    expression_parser.add_dlc(std::make_shared<UnaryOpParser>(Priority::PM_EXPRESSION, TokenList({"XOR"})));

    EXPECT_EQ(ExpressionChecker("1 ~ 2", expression_parser).str_messages(),
              "Unknown binary op ~\n");
    EXPECT_EQ(ExpressionChecker("^ 3", expression_parser).str_messages(),
              "Unknown unary op ^\n");
}

TEST(ExpressionParserDeathTest, unsupported_binary_parsers) {
    ExpressionParser expression_parser;
    ASSERT_DEATH((
            expression_parser.add_dlc(std::make_shared<BinaryOpParser>(Priority::AND_EXPRESSION, TokenList({"BITAND"})))
    ), "Assertion failed!");
}

TEST(ExpressionParserDeathTest, too_long_literal) {
    ASSERT_ANY_THROW((
            ExpressionChecker("1000000000000000000000000000").value()
    ));
}
