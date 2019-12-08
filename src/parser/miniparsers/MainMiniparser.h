#pragma once

#include "BlockMiniparser.h"

class MainMiniparser : public BlockMiniparser {
protected:
    std::unique_ptr<ASTEvent> try_eat_self_end_block(Lexer& lexer) override;
};
