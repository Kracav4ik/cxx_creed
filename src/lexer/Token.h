#pragma once

#include <string>

struct Token {
    bool valid() const {
        return !type.empty();
    }
    explicit operator bool() const {
        return valid();
    }

    std::string type;
    std::string text;
};
