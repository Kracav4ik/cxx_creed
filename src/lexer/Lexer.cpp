#include "Lexer.h"
#include "lexer/Token.h"

void Lexer::set_text(std::string text) {
    _text = std::move(text);
    _pos = 0;
}

Token Lexer::next_token() {
    if (_pos == _text.size()) {
        return {"EOF", ""};
    }
    Token result{"UNKNOWN", _text.substr(_pos, 1)};
    ++_pos;
    return result;
}
