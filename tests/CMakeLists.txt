add_subdirectory(googletest-1.10.0)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(creed_tests LexerTests.cpp)

target_link_libraries(creed_tests gtest gtest_main creed_common)
