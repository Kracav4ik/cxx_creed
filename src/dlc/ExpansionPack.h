#pragma once

class Lexer;
class Parser;
class Interpreter;

class ExpansionPack {
public:
    void install(Lexer& lexer, Parser& parser, Interpreter& interpreter);
};
