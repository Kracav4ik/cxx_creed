#include "IdentifierLexer.h"

IdentifierLexer::IdentifierLexer() : RegexpLexer("IDENTIFIER", "[a-zA-Z_][a-zA-Z0-9_]*") {}
