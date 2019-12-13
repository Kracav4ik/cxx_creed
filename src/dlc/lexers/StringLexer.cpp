#include "StringLexer.h"

StringLexer::StringLexer() : RegexpLexer("STRING", R"("([^"\r\n\\]|(\\["0abfnrtv\\]))*")") {}
