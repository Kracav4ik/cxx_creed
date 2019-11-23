add_subdirectory(googletest-1.10.0)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCES
        LexerTests.cpp
        ParserTests.cpp

        helpers/EventRecorder.cpp
        helpers/EventRecorder.h
        helpers/ParserChecker.cpp
        helpers/ParserChecker.h
        helpers/types.h
)

add_executable(creed_tests ${TEST_SOURCES})

target_link_libraries(creed_tests gtest gtest_main creed_common)
