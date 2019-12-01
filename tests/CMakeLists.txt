add_subdirectory(googletest-1.10.0)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCES
        EvaluatorTests.cpp
        ExpressionParserTests.cpp
        InterpreterTests.cpp
        LexerTests.cpp
        ParserTests.cpp

        helpers/ASTNodeString.cpp
        helpers/ASTNodeString.h
        helpers/EventRecorder.cpp
        helpers/EventRecorder.h
        helpers/ExpressionChecker.cpp
        helpers/ExpressionChecker.h
        helpers/InterpreterChecker.cpp
        helpers/InterpreterChecker.h
        helpers/ParserChecker.cpp
        helpers/ParserChecker.h
        helpers/types.h
        helpers/TestPrinter.cpp
        helpers/TestPrinter.h
)

add_executable(creed_tests ${TEST_SOURCES})

target_link_libraries(creed_tests gtest gtest_main creed_common)
