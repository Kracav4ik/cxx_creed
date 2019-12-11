#include "MainMiniparser.h"

#include "lexer/Lexer.h"
#include "lexer/Token.h"

#include "parser/events/BeginMainDeclEvent.h"
#include "parser/events/EndMainDeclEvent.h"

std::shared_ptr<ASTEvent> MainMiniparser::try_eat_begin_main(Lexer& lexer) {
    auto state = lexer.get_state();
    for (auto token_type : {"INT", "IDENTIFIER", "LPAR", "RPAR", "LBRACE"}) {
        auto token = lexer.next_token_with_type(token_type);
        if (!token.valid() || (token.type == "IDENTIFIER" && token.text != "main")) {
            return nullptr;
        }
    }
    state.drop();
    _main_begin = true;
    return std::make_shared<BeginMainDeclEvent>();
}

std::shared_ptr<ASTEvent> MainMiniparser::try_next_event(Lexer& lexer) {
    if (!_main_begin) {
        return try_eat_begin_main(lexer);
    }
    return BlockMiniparser::try_next_event(lexer);
}

std::shared_ptr<ASTEvent> MainMiniparser::end_block_ast_event() {
    return std::make_shared<EndMainDeclEvent>();
}
