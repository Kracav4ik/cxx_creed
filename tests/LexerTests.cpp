#include "gtest/gtest.h"

#include "dlc/lexers/ExactLexer.h"
#include "dlc/lexers/IdentifierLexer.h"
#include "dlc/lexers/IntegerLexer.h"
#include "dlc/lexers/StringLexer.h"
#include "dlc/lexers/NewlineLexer.h"
#include "dlc/lexers/RegexpLexer.h"
#include "dlc/lexers/WhitespaceLexer.h"
#include "dlc/lexers/LineCommentLexer.h"
#include "dlc/lexers/BlockCommentLexer.h"

#define EXPECT_TOKEN(TOKEN, TEXT) EXPECT_EQ(std::string{(TOKEN).text}, (TEXT))

TEST(ExactLexerTest, exact_lexer) {
    ExactLexer lexer("EXACTTEST", "test");
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("testtest"), "test");
    EXPECT_TOKEN(lexer.try_consume("est"), "");
    EXPECT_TOKEN(lexer.try_consume(" test"), "");
}

TEST(ExactLexerTest, exact_lexer_no_regexp) {
    ExactLexer lexer("EXACTTEST", ".+");
    EXPECT_TOKEN(lexer.try_consume("m"), "");
    EXPECT_TOKEN(lexer.try_consume("."), "");
    EXPECT_TOKEN(lexer.try_consume(".+"), ".+");
}

TEST(IdentifierLexerTest, identifier_lexer) {
    IdentifierLexer lexer;
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("test"), "test");
    EXPECT_TOKEN(lexer.try_consume("_tesT12 test"), "_tesT12");
    EXPECT_TOKEN(lexer.try_consume("test,test"), "test");
    EXPECT_TOKEN(lexer.try_consume("0test"), "");
}

TEST(IntegerLexerTest, integer_lexer) {
    IntegerLexer lexer;
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("test"), "");
    EXPECT_TOKEN(lexer.try_consume("234_test"), "234");
    EXPECT_TOKEN(lexer.try_consume("12+34"), "12");
}

TEST(StringLexerTest, string_lexer) {
    StringLexer lexer;
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume(R"(")"), "");
    EXPECT_TOKEN(lexer.try_consume(R"("")"), R"("")");
    EXPECT_TOKEN(lexer.try_consume(R"(""")"), R"("")");
    EXPECT_TOKEN(lexer.try_consume(R"("""")"), R"("")");
    EXPECT_TOKEN(lexer.try_consume(R"("abc")"), R"("abc")");
    EXPECT_TOKEN(lexer.try_consume(R"("\")"), "");
    EXPECT_TOKEN(lexer.try_consume(R"("\\")"), R"("\\")");
    EXPECT_TOKEN(lexer.try_consume(R"("\\\")"), "");
    EXPECT_TOKEN(lexer.try_consume(R"("\\\\")"), R"("\\\\")");
    EXPECT_TOKEN(lexer.try_consume(R"("\"")"), R"("\"")");
    EXPECT_TOKEN(lexer.try_consume(R"("\0")"), R"("\0")");
    EXPECT_TOKEN(lexer.try_consume(R"("\a")"), R"("\a")");
    EXPECT_TOKEN(lexer.try_consume(R"("\b")"), R"("\b")");
    EXPECT_TOKEN(lexer.try_consume(R"("\f")"), R"("\f")");
    EXPECT_TOKEN(lexer.try_consume(R"("\n")"), R"("\n")");
    EXPECT_TOKEN(lexer.try_consume(R"("\r")"), R"("\r")");
    EXPECT_TOKEN(lexer.try_consume(R"("\t")"), R"("\t")");
    EXPECT_TOKEN(lexer.try_consume(R"("\v")"), R"("\v")");

    EXPECT_TOKEN(lexer.try_consume(R"(')"), "");
    EXPECT_TOKEN(lexer.try_consume(R"('')"), "");
    EXPECT_TOKEN(lexer.try_consume(R"("\1")"), "");
    EXPECT_TOKEN(lexer.try_consume(R"("\x00")"), "");
    EXPECT_TOKEN(lexer.try_consume("\" \n \""), "");
    EXPECT_TOKEN(lexer.try_consume("\" \r \""), "");
    EXPECT_TOKEN(lexer.try_consume("\" \a \b \f \t \v \""), "\" \a \b \f \t \v \"");
}

TEST(NewlineLexerTest, newline_lexer) {
    NewlineLexer lexer;
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("te\nst"), "");
    EXPECT_TOKEN(lexer.try_consume("\n234_test"), "\n");
    EXPECT_TOKEN(lexer.try_consume("\n\n\n"), "\n");
    EXPECT_TOKEN(lexer.try_consume(" \n"), "");
}

TEST(RegexpLexerTest, regexp_lexer) {
    RegexpLexer lexer("REGTEST", "abc?[def]+");
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("abd"), "abd");
    EXPECT_TOKEN(lexer.try_consume("abce"), "abce");
    EXPECT_TOKEN(lexer.try_consume("abcabcd"), "");
    EXPECT_TOKEN(lexer.try_consume("abc"), "");
}

TEST(WhitespaceLexerTest, whitespace_lexer) {
    WhitespaceLexer lexer;
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("test      "), "");
    EXPECT_TOKEN(lexer.try_consume("              234_test"), "              ");
    EXPECT_TOKEN(lexer.try_consume(" \t \r \f \v \n "), " \t \r \f \v ");
}

TEST(LineCommentLexerTest, comment_lexer) {
    LineCommentLexer lexer;
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("//\n"), "//\n");
    EXPECT_TOKEN(lexer.try_consume("// abc \n"), "// abc \n");
    EXPECT_TOKEN(lexer.try_consume("// abc"), "// abc");
    EXPECT_TOKEN(lexer.try_consume("// abc \n ced \n"), "// abc \n");

    EXPECT_TOKEN(lexer.try_consume("// /*   */ \n"), "// /*   */ \n");
    EXPECT_TOKEN(lexer.try_consume("// abc /* ced \n def */ feg \n"), "// abc /* ced \n");
    EXPECT_TOKEN(lexer.try_consume("/*//    */ \n"), "");
    EXPECT_TOKEN(lexer.try_consume("/* abc \n // ced \n def */ \n"), "");
}

TEST(BlockCommentLexerTest, comment_lexer) {
    BlockCommentLexer lexer;
    EXPECT_TOKEN(lexer.try_consume(""), "");
    EXPECT_TOKEN(lexer.try_consume("// \n"), "");

    EXPECT_TOKEN(lexer.try_consume("/* abc */"), "/* abc */");
    EXPECT_TOKEN(lexer.try_consume("/* abc */ /* ced */"), "/* abc */");
    EXPECT_TOKEN(lexer.try_consume("/* abc \n ced \n def */ \n"), "/* abc \n ced \n def */");

    EXPECT_TOKEN(lexer.try_consume("// /*   */ \n"), "");
    EXPECT_TOKEN(lexer.try_consume("/* abc \n // ced \n def */ \n"), "/* abc \n // ced \n def */");
}
