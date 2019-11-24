#include "gtest/gtest.h"

#include "helpers/ExpressionChecker.h"

TEST(ExpressionParserTest, arithmetics) {
    EXPECT_EQ(ExpressionChecker("1").str(), "[Integer 1]");

    EXPECT_EQ(ExpressionChecker("1 + 2").str(), "[BinaryOp [Integer 1] + [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 - 2").str(), "[BinaryOp [Integer 1] - [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 * 2").str(), "[BinaryOp [Integer 1] * [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 / 2").str(), "[BinaryOp [Integer 1] / [Integer 2]]");
    EXPECT_EQ(ExpressionChecker("1 % 2").str(), "[BinaryOp [Integer 1] % [Integer 2]]");

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
    EXPECT_EQ(ExpressionChecker("()").str(), "");
    EXPECT_EQ(ExpressionChecker("(1)").str(), "[Integer 1]");
    EXPECT_EQ(ExpressionChecker("(3 + 5)").str(), "[BinaryOp [Integer 3] + [Integer 5]]");
    EXPECT_EQ(ExpressionChecker("2 * (3 + 5)").str(), "[BinaryOp [Integer 2] * [BinaryOp [Integer 3] + [Integer 5]]]");
}
