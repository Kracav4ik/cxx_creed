#pragma once

#include <string>

class ExpressionChecker {
public:
    explicit ExpressionChecker(std::string expression);
    const std::string& str() const;

private:
    std::string _str;
};
