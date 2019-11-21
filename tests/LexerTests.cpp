#include "gtest/gtest.h"

#include "dlc/lexers/ExactLexer.h"
#include "dlc/lexers/IdentifierLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/NewlineLexer.h"
#include "dlc/lexers/RegexpLexer.h"
#include "dlc/lexers/WhitespaceLexer.h"


TEST(ExactLexerTest, exact_lexer) {
    ExactLexer lexer("EXACTTEST", "test");
    EXPECT_EQ(lexer.try_consume("").text, "");
    EXPECT_EQ(lexer.try_consume("testtest").text, "test");
    EXPECT_EQ(lexer.try_consume("est").text, "");
    EXPECT_EQ(lexer.try_consume(" test").text, "");
}

TEST(ExactLexerTest, exact_lexer_no_regexp) {
    ExactLexer lexer("EXACTTEST", ".+");
    EXPECT_EQ(lexer.try_consume("m").text, "");
    EXPECT_EQ(lexer.try_consume(".").text, "");
    EXPECT_EQ(lexer.try_consume(".+").text, ".+");
}

TEST(IdentifierLexerTest, identifier_lexer) {
    IdentifierLexer lexer;
    EXPECT_EQ(lexer.try_consume("").text, "");
    EXPECT_EQ(lexer.try_consume("test").text, "test");
    EXPECT_EQ(lexer.try_consume("_tesT12 test").text, "_tesT12");
    EXPECT_EQ(lexer.try_consume("test,test").text, "test");
    EXPECT_EQ(lexer.try_consume("0test").text, "");
}

TEST(IntegerLexerTest, integer_lexer) {
    IntegerLexer lexer;
    EXPECT_EQ(lexer.try_consume("").text, "");
    EXPECT_EQ(lexer.try_consume("test").text, "");
    EXPECT_EQ(lexer.try_consume("234_test").text, "234");
    EXPECT_EQ(lexer.try_consume("12+34").text, "12");
}

TEST(NewlineLexerTest, newline_lexer) {
    NewlineLexer lexer;
    EXPECT_EQ(lexer.try_consume("").text, "");
    EXPECT_EQ(lexer.try_consume("te\nst").text, "");
    EXPECT_EQ(lexer.try_consume("\n234_test").text, "\n");
    EXPECT_EQ(lexer.try_consume("\n\n\n").text, "\n");
    EXPECT_EQ(lexer.try_consume(" \n").text, "");
}

TEST(RegexpLexerTest, regexp_lexer) {
    RegexpLexer lexer("REGTEST", "abc?[def]+");
    EXPECT_EQ(lexer.try_consume("").text, "");
    EXPECT_EQ(lexer.try_consume("abd").text, "abd");
    EXPECT_EQ(lexer.try_consume("abce").text, "abce");
    EXPECT_EQ(lexer.try_consume("abcabcd").text, "");
    EXPECT_EQ(lexer.try_consume("abc").text, "");
}

TEST(WhitespaceLexerTest, whitespace_lexer) {
    WhitespaceLexer lexer;
    EXPECT_EQ(lexer.try_consume("").text, "");
    EXPECT_EQ(lexer.try_consume("test      ").text, "");
    EXPECT_EQ(lexer.try_consume("              234_test").text, "              ");
    EXPECT_EQ(lexer.try_consume(" \t \r \f \v \n ").text, " \t \r \f \v ");
}
