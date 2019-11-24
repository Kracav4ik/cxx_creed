#include "gtest/gtest.h"

#include "helpers/ExpressionChecker.h"

TEST(EvaluatorTest, simple_arithmetics) {
    EXPECT_EQ(ExpressionChecker("").value(), 0);

    EXPECT_EQ(ExpressionChecker("+ 3").value(), 3);
    EXPECT_EQ(ExpressionChecker("- 3").value(), -3);

    EXPECT_EQ(ExpressionChecker("20 + 3").value(), 23);
    EXPECT_EQ(ExpressionChecker("20 - 3").value(), 17);
    EXPECT_EQ(ExpressionChecker("20 * 3").value(), 60);
    EXPECT_EQ(ExpressionChecker("20 / 3").value(), 6);
    EXPECT_EQ(ExpressionChecker("20 / -3").value(), -6);
    EXPECT_EQ(ExpressionChecker("-20 / 3").value(), -6);
    EXPECT_EQ(ExpressionChecker("20 % 3").value(), 2);
    EXPECT_EQ(ExpressionChecker("-20 % 3").value(), -2);
    EXPECT_EQ(ExpressionChecker("20 % -3").value(), 2);

    EXPECT_EQ(ExpressionChecker("20 % 3").value(), 2);
}

TEST(EvaluatorTest, complex_arithmetics) {
    EXPECT_EQ(ExpressionChecker("(13 + 45) % (2 + 3)").value(), 3);
    EXPECT_EQ(ExpressionChecker("4 * (13 + 45) / (2 + 3)").value(), 46);
    EXPECT_EQ(ExpressionChecker("(15 - 45) * 3 - 125 / 4").value(), -121);
    EXPECT_EQ(ExpressionChecker("5 + ((15 - 45) * 3 - 125) / 4").value(), -48);
    EXPECT_EQ(ExpressionChecker("10 - ((20 - 5 - (20 + 25) * 3) - 125) / 4 + 6").value(), 77);
}
