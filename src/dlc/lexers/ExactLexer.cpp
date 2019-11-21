#include "ExactLexer.h"

#include <utility>

ConsumeResult ExactLexer::try_consume(std::string_view text) {
    size_t size = 0;
    if (text.substr(0, _token.size()) == _token) {
        size = _token.size();
    }

    return {_type, text.substr(0, size)};
}

ExactLexer::ExactLexer(std::string type, std::string token) : _type(std::move(type)), _token(std::move(token)) {}
