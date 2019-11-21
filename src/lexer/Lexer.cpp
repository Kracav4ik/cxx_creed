#include "Lexer.h"
#include "lexer/Token.h"

void Lexer::set_text(std::string text) {
    _text = std::move(text);
    _pos = 0;
}

Token Lexer::next_token() {
    if (_pos >= _text.size()) {
        return {"EOF", ""};
    }

    auto text = current_text();
    ConsumeResult max_consume;
    for (const auto& lexer : _dlcList) {
        auto consumeResult = lexer->try_consume(text);
        if (consumeResult.is_consumed() && consumeResult.consumed_size() > max_consume.consumed_size()) {
            max_consume = std::move(consumeResult);
        }
    }
    if (max_consume.is_consumed()) {
        return {std::move(max_consume.type), consume(max_consume.consumed_size())};
    }

    return {"UNKNOWN", consume(1)};
}

std::string Lexer::consume(size_t amount) {
    auto result = _text.substr(_pos, amount);
    _pos += amount;
    return result;
}

std::string_view Lexer::current_text() const {
    std::string_view view = _text;
    return view.substr(_pos);
}
