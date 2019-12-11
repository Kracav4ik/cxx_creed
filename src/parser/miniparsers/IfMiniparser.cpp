#include "IfMiniparser.h"

#include "parser/events/EndIfDeclEvent.h"

std::unique_ptr<ASTEvent> IfMiniparser::end_block_ast_event() {
    return std::make_unique<EndIfDeclEvent>();
}
