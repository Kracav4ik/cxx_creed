#pragma once

#include <string>

struct Token {
    bool valid() const {
        return !type.empty();
    }

    std::string type;
    std::string text;
};
