#include "gtest/gtest.h"

#include "helpers/ParserChecker.h"
#include "helpers/types.h"

TEST(ParserTest, simple_main) {
    EXPECT_EQ(ParserChecker("int main() { return 0; }").events(), Strings({
            "BeginMainDecl", "ReturnStmt [Integer 0]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { return 123456; }").events(), Strings({
            "BeginMainDecl", "ReturnStmt [Integer 123456]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { int x; }").events(), Strings({
            "BeginMainDecl", "VarDecl x", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { }").events(), Strings({
            "BeginMainDecl", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { } int x;").events(), Strings({
            "BeginMainDecl", "EndMainDecl", "UnknownTokenType INT", "UnknownTokenType IDENTIFIER", "UnknownTokenType SEMICOLON"
    }));
    EXPECT_EQ(ParserChecker("int main() { } return x;").events(), Strings({
            "BeginMainDecl", "EndMainDecl", "UnknownTokenType RETURN", "UnknownTokenType IDENTIFIER", "UnknownTokenType SEMICOLON"
    }));
    EXPECT_EQ(ParserChecker("int main() { } x = 2;").events(), Strings({
            "BeginMainDecl", "EndMainDecl", "UnknownTokenType IDENTIFIER", "UnknownTokenType ASSIGN", "UnknownTokenType INTEGER", "UnknownTokenType SEMICOLON"
    }));
    EXPECT_EQ(ParserChecker("int main() { return 0; return 0; }").events(), Strings({
            "BeginMainDecl", "ReturnStmt [Integer 0]", "ReturnStmt [Integer 0]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { x = 3; }").events(), Strings({
            "BeginMainDecl", "ExprStmt [AssignmentOp [Variable x] = [Integer 3]]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { 2 = x; }").events(), Strings({
            "BeginMainDecl", "ExprStmt [AssignmentOp [Integer 2] = [Variable x]]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { x = x; }").events(), Strings({
            "BeginMainDecl", "ExprStmt [AssignmentOp [Variable x] = [Variable x]]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { x = 1 + 2; }").events(), Strings({
            "BeginMainDecl", "ExprStmt [AssignmentOp [Variable x] = [BinaryOp [Integer 1] + [Integer 2]]]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { x; }").events(), Strings({
            "BeginMainDecl", "ExprStmt [Variable x]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { 3; }").events(), Strings({
            "BeginMainDecl", "ExprStmt [Integer 3]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { 3 + 2 * 3; }").events(), Strings({
            "BeginMainDecl", "ExprStmt [BinaryOp [Integer 3] + [BinaryOp [Integer 2] * [Integer 3]]]", "EndMainDecl"
    }));
}

TEST(ParserTest, block_tests) {
    EXPECT_EQ(ParserChecker("int main() { { return 0;} }").events(), Strings({
            "BeginMainDecl", "BeginBlockStmt", "ReturnStmt [Integer 0]", "EndBlockStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { {  } }").events(), Strings({
            "BeginMainDecl", "BeginBlockStmt", "EndBlockStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { {  } } }").events(), Strings({
            "BeginMainDecl", "BeginBlockStmt", "BeginBlockStmt", "EndBlockStmt", "EndBlockStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { } return 0; }").events(), Strings({
            "BeginMainDecl", "BeginBlockStmt", "EndBlockStmt", "ReturnStmt [Integer 0]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { int x; } { return 0; } }").events(), Strings({
            "BeginMainDecl", "BeginBlockStmt", "VarDecl x", "EndBlockStmt", "BeginBlockStmt", "ReturnStmt [Integer 0]", "EndBlockStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { return 0; } x + 5; }").events(), Strings({
            "BeginMainDecl", "BeginBlockStmt", "ReturnStmt [Integer 0]", "EndBlockStmt", "ExprStmt [BinaryOp [Variable x] + [Integer 5]]", "EndMainDecl"
    }));
}

TEST(ParserTest, function_tests) {
    EXPECT_EQ(ParserChecker("int main() { int main() {} }").events(), Strings({
        "BeginMainDecl",
            "UnknownTokenType INT", "UnknownTokenType IDENTIFIER", "UnknownTokenType LPAR", "UnknownTokenType RPAR",
            "BeginBlockStmt", "EndBlockStmt",
        "EndMainDecl"
    }));
}

TEST(ParserTest, conditions_tests) {
    EXPECT_EQ(ParserChecker("int main() { if (1) { return 0; } }").events(), Strings({
        "BeginMainDecl", "BeginIfStmt [Integer 1]", "ReturnStmt [Integer 0]", "EndIfStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { if (1) { return 0; } } }").events(), Strings({
        "BeginMainDecl", "BeginBlockStmt",
            "BeginIfStmt [Integer 1]", "ReturnStmt [Integer 0]", "EndIfStmt",
        "EndBlockStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { if (1) { { return 0; } } }").events(), Strings({
        "BeginMainDecl", "BeginIfStmt [Integer 1]",
            "BeginBlockStmt", "ReturnStmt [Integer 0]", "EndBlockStmt",
        "EndIfStmt", "EndMainDecl"
    }));
}

TEST(ParserTest, loops_tests) {
    EXPECT_EQ(ParserChecker("int main() { while (1) { return 0; } }").events(), Strings({
        "BeginMainDecl", "BeginWhileStmt [Integer 1]", "ReturnStmt [Integer 0]", "EndWhileStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { while (1) { return 0; } } }").events(), Strings({
        "BeginMainDecl", "BeginBlockStmt",
            "BeginWhileStmt [Integer 1]", "ReturnStmt [Integer 0]", "EndWhileStmt",
        "EndBlockStmt", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { while (1) { { return 0; } } }").events(), Strings({
        "BeginMainDecl", "BeginWhileStmt [Integer 1]",
            "BeginBlockStmt", "ReturnStmt [Integer 0]", "EndBlockStmt",
        "EndWhileStmt", "EndMainDecl"
    }));
}
