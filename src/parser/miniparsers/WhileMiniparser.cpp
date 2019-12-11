#include "WhileMiniparser.h"

#include "parser/events/EndWhileStmtEvent.h"

std::shared_ptr<ASTEvent> WhileMiniparser::end_block_ast_event() {
    return std::make_shared<EndWhileStmtEvent>();
}
