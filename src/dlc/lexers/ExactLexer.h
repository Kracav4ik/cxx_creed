#pragma once

#include "dlc/LexerDLC.h"

class ExactLexer : public LexerDLC {
public:
    ExactLexer(std::string type, std::string token);
    ConsumeResult try_consume(std::string_view text) const override;

private:
    std::string _type;
    std::string _token;
};
