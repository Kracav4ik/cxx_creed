#include "gtest/gtest.h"

#include "helpers/InterpreterChecker.h"

TEST(InterpreterTests, basics) {
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        return 6*100 + 6*10 + 6;
    })").output(), ">>> return value `666`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        return 2;
        return 6;
    })").output(), ">>> return value `2`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        x = 5 + 3 * 2;
        return x * x;
    })").output(), ">>> return value `121`\n");
    // TODO: have "uninitialized" variable value
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        return x + 2;
    })").output(), ">>> return value `2`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        x = x;
        return x + 2;
    })").output(), ">>> return value `2`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        x = 5;
        x = 3;
        return x * x;
    })").output(), ">>> return value `9`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        ( ( ( x ) ) ) = 5;
        x;
        return x * x;
    })").output(), ">>> return value `25`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        int y;
        int z;
        x = y = z = 5;
        y = (x = 3 + y) - z;
        return 100 * x + 10 * y + z;
    })").output(), ">>> return value `835`\n");
}

TEST(InterpreterTests, blocks) {
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        {
            x = 5;
        }
        x;
        return x * x;
    })").output(), ">>> return value `25`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        {
            x = 2;
            {
                return x * x;
            }
        }
    })").output(), ">>> return value `4`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        {
            int x;
            x = 2;
        }
        return x + 3;
    })").output(), "Unknown variable name x\n>>> return value `3`\n");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        x = 1;
        int y;
        y = 0;
        {
            y = y + x;              // 1
            x = 2;
            y = y + 10*x;           // 2
            int x;
            x = 3;
            y = y + 100*x;          // 3
            {
                y = y + 1000*x;     // 3
                int x;
                y = y + 10000*x;    // 0
                x = 4;
                y = y + 100000*x;   // 4
            }
            y = y + 1000000*x;      // 3
        }
        y = y + 10000000*x;         // 2
        return y;
    })").output(), ">>> return value `23403321`\n");
}

TEST(InterpreterTests, with_errors) {
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        // no return
    })").output(), "main() did not return a value\n");

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        return 2)").output(), (
R"(Unknown token type: RETURN
Unknown token type: INTEGER
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        return 2 // no semicolon
    })").output(), (
R"(Unknown token type: RETURN
Unknown token type: INTEGER
main() did not return a value
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        return 5; $
    }
    int x;
    )").output(), (
R"(>>> return value `5`
Unknown token: `$`
Unknown token type: INT
Unknown token type: IDENTIFIER
Unknown token type: SEMICOLON
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        return x;
    })").output(), (
R"(Unknown variable name x
>>> return value `0`
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        x = x;
        return 2;
    })").output(), (
R"(Unknown variable name x
Cannot assign to undeclared variable x
>>> return value `2`
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int y;
        y = (x = x + 5);
        return 2 + y;
    })").output(), (
R"(Unknown variable name x
Cannot assign to undeclared variable x
>>> return value `7`
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        x = 5;
        int x;
        return x;
    })").output(), (
R"(Variable x already declared
>>> return value `5`
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        2 = 4;
        return 7;
    })").output(), (
R"(No variable to assign to
>>> return value `7`
)"));

    EXPECT_EQ(InterpreterChecker(R"(int main() {
        {
            int x;
        }
        x;
        return x * x;
    })").output(), R"(Unknown variable name x
Unknown variable name x
Unknown variable name x
>>> return value `0`
)");
    EXPECT_EQ(InterpreterChecker(R"(int main() {
        int x;
        {
            int x;
            int x;
        }
        return 0;
    })").output(), R"(Variable x already declared
>>> return value `0`
)");
}
