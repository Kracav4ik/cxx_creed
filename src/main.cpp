#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "interpreter/Interpreter.h"
#include "dlc/ExpansionPack.h"
#include "util.h"

#include <iostream>

int main() {
    Lexer lexer;
    Parser parser(lexer);
    Interpreter interpreter(parser);

    ExpansionPack pack;
    pack.install(lexer, parser, interpreter);

    std::string text = read_file("../src/main.cpp");
    std::cout << "----------\n" << text << "\n----------" << std::endl;

    lexer.set_text(text);
    interpreter.run();

    return 0;
}
