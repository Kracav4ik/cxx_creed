#include "IfMiniparser.h"

#include "parser/events/EndIfStmtEvent.h"

std::shared_ptr<ASTEvent> IfMiniparser::end_block_ast_event() {
    return std::make_shared<EndIfStmtEvent>();
}
