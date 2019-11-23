#include "LineCommentLexer.h"

LineCommentLexer::LineCommentLexer() : RegexpLexer("COMMENT", "//.*\n|//.*$") {}
