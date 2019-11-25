#include "gtest/gtest.h"

#include "helpers/ExpressionChecker.h"

TEST(EvaluatorTest, simple_arithmetics) {
    EXPECT_EQ(ExpressionChecker("").value(), 0);

    EXPECT_EQ(ExpressionChecker("+ 3").value(), 3);
    EXPECT_EQ(ExpressionChecker("- 3").value(), -3);
    EXPECT_EQ(ExpressionChecker("~3").value(), -4);
    EXPECT_EQ(ExpressionChecker("~-5").value(), 4);

    EXPECT_EQ(ExpressionChecker("20 + 3").value(), 23);
    EXPECT_EQ(ExpressionChecker("20 - 3").value(), 17);
    EXPECT_EQ(ExpressionChecker("20 * 3").value(), 60);
    EXPECT_EQ(ExpressionChecker("20 / 3").value(), 6);
    EXPECT_EQ(ExpressionChecker("20 / -3").value(), -6);
    EXPECT_EQ(ExpressionChecker("-20 / 3").value(), -6);
    EXPECT_EQ(ExpressionChecker("20 % 3").value(), 2);
    EXPECT_EQ(ExpressionChecker("-20 % 3").value(), -2);
    EXPECT_EQ(ExpressionChecker("20 % -3").value(), 2);

    EXPECT_EQ(ExpressionChecker("21 ^ 3").value(), 22);
    EXPECT_EQ(ExpressionChecker("21 & 3").value(), 1);
    EXPECT_EQ(ExpressionChecker("20 | 3").value(), 23);
    EXPECT_EQ(ExpressionChecker("20 << 3").value(), 160);
    EXPECT_EQ(ExpressionChecker("15 >> 3").value(), 1);
}

TEST(EvaluatorTest, complex_arithmetics) {
    EXPECT_EQ(ExpressionChecker("(13 + 45) % (2 + 3)").value(), 3);
    EXPECT_EQ(ExpressionChecker("4 * (13 + 45) / (2 + 3)").value(), 46);
    EXPECT_EQ(ExpressionChecker("(15 - 45) * 3 - 125 / 4").value(), -121);
    EXPECT_EQ(ExpressionChecker("5 + ((15 - 45) * 3 - 125) / 4").value(), -48);
    EXPECT_EQ(ExpressionChecker("10 - ((20 - 5 - (20 + 25) * 3) - 125) / 4 + 6").value(), 77);
}

TEST(EvaluatorTest, binary_priority) {
    EXPECT_EQ(ExpressionChecker("5 | 3 ^ 1").value(), 7);
    EXPECT_EQ(ExpressionChecker("(5 | 3) ^ 1").value(), 6);
    EXPECT_EQ(ExpressionChecker("5 ^ 14 & 8").value(), 13);
    EXPECT_EQ(ExpressionChecker("(5 ^ 14) & 8").value(), 8);

    EXPECT_EQ(ExpressionChecker("9 & 3 << 2").value(), 8);
    EXPECT_EQ(ExpressionChecker("(9 & 3) << 2").value(), 4);
    EXPECT_EQ(ExpressionChecker("11 & 31 >> 2").value(), 3);
    EXPECT_EQ(ExpressionChecker("(11 & 31) >> 2").value(), 2);

    EXPECT_EQ(ExpressionChecker("1 << 4 + 3").value(), 128);
    EXPECT_EQ(ExpressionChecker("(1 << 4) + 3").value(), 19);
    EXPECT_EQ(ExpressionChecker("1 << 4 - 3").value(), 2);
    EXPECT_EQ(ExpressionChecker("(1 << 4) - 3").value(), 13);

    EXPECT_EQ(ExpressionChecker("1 + 5 * 3").value(), 16);
    EXPECT_EQ(ExpressionChecker("(1 + 5) * 3").value(), 18);
    EXPECT_EQ(ExpressionChecker("1 + 10 / 3").value(), 4);
    EXPECT_EQ(ExpressionChecker("(1 + 10) / 3").value(), 3);
    EXPECT_EQ(ExpressionChecker("1 + 20 % 3").value(), 3);
    EXPECT_EQ(ExpressionChecker("(1 + 20) % 3").value(), 0);
}
