#include "IdentifierLexer.h"

IdentifierLexer::IdentifierLexer() : RegexpLexer("IDENTIFIER", "[a-zA-Z_]\\w*(::[a-zA-Z_]\\w*)*") {}
