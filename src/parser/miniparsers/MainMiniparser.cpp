#include "MainMiniparser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/EndMainDeclEvent.h"

std::unique_ptr<ASTEvent> MainMiniparser::try_eat_self_end_block(Lexer& lexer) {
    auto state = lexer.get_state();
    if (auto token = lexer.next_token_with_type("RBRACE")) {
        state.drop();
        _completed = true;
        return std::make_unique<EndMainDeclEvent>();
    }
    return nullptr;
}
