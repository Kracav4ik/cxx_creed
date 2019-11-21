#pragma once
#include "dlc/LexerDLC.h"

class NewlineLexer : public LexerDLC {
public:
    ConsumeResult try_consume(std::string_view text) override;
};
