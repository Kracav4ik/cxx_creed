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
            "BeginMainDecl", "BeginBlockDecl", "ReturnStmt [Integer 0]", "EndBlockDecl", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { {  } }").events(), Strings({
            "BeginMainDecl", "BeginBlockDecl", "EndBlockDecl", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { {  } } }").events(), Strings({
            "BeginMainDecl", "BeginBlockDecl", "BeginBlockDecl", "EndBlockDecl", "EndBlockDecl", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { } return 0; }").events(), Strings({
            "BeginMainDecl", "BeginBlockDecl", "EndBlockDecl", "ReturnStmt [Integer 0]", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { int x; } { return 0; } }").events(), Strings({
            "BeginMainDecl", "BeginBlockDecl", "VarDecl x", "EndBlockDecl", "BeginBlockDecl", "ReturnStmt [Integer 0]", "EndBlockDecl", "EndMainDecl"
    }));
    EXPECT_EQ(ParserChecker("int main() { { return 0; } x + 5; }").events(), Strings({
            "BeginMainDecl", "BeginBlockDecl", "ReturnStmt [Integer 0]", "EndBlockDecl", "ExprStmt [BinaryOp [Variable x] + [Integer 5]]", "EndMainDecl"
    }));
}

TEST(ParserTest, function_tests) {
    EXPECT_EQ(ParserChecker("int main() { int main() {} }").events(), Strings({
        "BeginMainDecl",
            "UnknownTokenType INT", "UnknownTokenType IDENTIFIER", "UnknownTokenType LPAR", "UnknownTokenType RPAR",
            "BeginBlockDecl", "EndBlockDecl",
        "EndMainDecl"
    }));
}
