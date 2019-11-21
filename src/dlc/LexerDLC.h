#pragma once

#include <string>
#include <string_view>

struct ConsumeResult {
    std::string type;
    std::string_view text;

    size_t consumed_size() const { return text.size(); }
    bool is_consumed() const { return !text.empty(); }
};

struct LexerDLC {
    virtual ~LexerDLC() = default;
    virtual ConsumeResult try_consume(std::string_view text) = 0;
};
