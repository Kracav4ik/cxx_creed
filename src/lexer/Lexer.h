#pragma once

#include "dlc/WithDLC.h"
#include "dlc/LexerDLC.h"

#include <string>

struct Token;

class Lexer : public WithDLC<LexerDLC> {
public:
    void set_text(std::string text);

    Token next_token();

private:
    std::string _text;
    size_t _pos = 0;
};

