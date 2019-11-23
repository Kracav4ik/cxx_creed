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
}
