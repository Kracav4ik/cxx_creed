#pragma once

#include "dlc/LexerDLC.h"

class WhitespaceLexer : public LexerDLC {
public:
    ConsumeResult try_consume(std::string_view text) const override;
};
