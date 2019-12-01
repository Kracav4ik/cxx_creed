#pragma once

#include <string>

class InterpreterChecker {
public:
    explicit InterpreterChecker(std::string code);

    const std::string& output() const;

private:
    std::string _output;
};
