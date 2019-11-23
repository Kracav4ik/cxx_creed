#pragma once

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "EventRecorder.h"

class ParserChecker {
public:
    explicit ParserChecker(std::string text);

    const Strings& events() const;

private:
    Lexer _lexer;
    Parser _parser;
    EventRecorder _recorder;
};
