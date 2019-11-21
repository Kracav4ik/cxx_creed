#pragma once
#include "dlc/LexerDLC.h"
#include <regex>

class RegexpLexer : public LexerDLC {
public:
    RegexpLexer(std::string type, const std::string& regexp);
    ConsumeResult try_consume(std::string_view text) override;

private:
    std::string _type;
    std::regex _regex;
};
