#include "WhitespaceLexer.h"

#include <cctype>

ConsumeResult WhitespaceLexer::try_consume(std::string_view text) const {
    size_t pos = 0;
    while (pos < text.size() && isspace(text[pos]) && text[pos] != '\n') {
        ++pos;
    }
    return {"WHITESPACE", text.substr(0, pos)};
}
