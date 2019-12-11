#pragma once

#include "BlockMiniparser.h"

class WhileMiniparser : public BlockMiniparser {
private:
    std::shared_ptr<ASTEvent> end_block_ast_event() override;
};
