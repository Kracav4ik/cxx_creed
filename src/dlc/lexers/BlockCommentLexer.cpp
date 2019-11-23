#include "BlockCommentLexer.h"

BlockCommentLexer::BlockCommentLexer() : RegexpLexer("COMMENT", R"(/\*(.|\n)*?\*/)") {}
