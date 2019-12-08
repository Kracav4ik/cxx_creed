#include "Lexer.h"
#include "lexer/Token.h"


bool better_consume(const ConsumeResult& new_result, const ConsumeResult& old_result) {
    if (new_result.consumed_size() > old_result.consumed_size()) {
        return true;
    }
    if (new_result.consumed_size() == old_result.consumed_size()) {
        return new_result.is_exact;
    }
    return false;
}

void Lexer::set_text(std::string text) {
    _text = std::move(text);
    _pos = 0;
}

Token Lexer::next_token(bool skip_space) {
    if (skip_space) {
        skip_whitespace();
    }
    if (_pos >= _text.size()) {
        return {"EOF", ""};
    }

    auto text = current_text();
    ConsumeResult max_consume;
    for (const auto& lexer : _dlc_list) {
        auto consume_result = lexer->try_consume(text);
        if (consume_result.is_consumed() && better_consume(consume_result, max_consume)) {
            max_consume = std::move(consume_result);
        }
    }
    if (max_consume.is_consumed()) {
        return {std::move(max_consume.type), consume(max_consume.consumed_size())};
    }

    return {"UNKNOWN", consume(1)};
}

void Lexer::skip_whitespace() {
    auto state = get_state();
    Token token = next_token(false);
    while (token.type == "WHITESPACE" || token.type == "NEWLINE" || token.type == "COMMENT") {
        state.assign(_pos);
        token = next_token(false);
    }
}

Token Lexer::next_token_with_type(const std::string& expected_type) {
    auto token = next_token();
    if (token.type == expected_type) {
        return token;
    } else {
        return {};
    }
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

Lexer::State Lexer::get_state() {
    return State(*this);
}

void Lexer::State::drop() {
    _dropped = true;
}

void Lexer::State::revert() {
    if (!_dropped) {
        _lexer._pos = _pos;
    }
    drop();
}

Lexer::State::~State() {
    revert();
}

Lexer::State::State(Lexer& lexer) : _lexer(lexer), _pos(lexer._pos) {}

void Lexer::State::assign(size_t pos) {
    _pos = pos;
}
