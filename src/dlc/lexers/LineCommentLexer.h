#pragma once

#include "dlc/lexers/RegexpLexer.h"

class LineCommentLexer : public RegexpLexer {
public:
    LineCommentLexer();
};
