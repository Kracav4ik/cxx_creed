#pragma once

#include <string>

struct Token {
    bool valid() const {
        return !type.empty();
    }
    explicit operator bool() const {
        return valid();
    }

    bool eof() const {
        return type == "EOF";
    }
    bool unknown() const {
        return type == "UNKNOWN";
    }

    static Token make_eof() { return {"EOF", ""}; }
    static Token make_unknown(std::string text) { return {"UNKNOWN", std::move(text)}; }

    std::string type;
    std::string text;
};
