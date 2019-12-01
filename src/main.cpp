#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "interpreter/Interpreter.h"
#include "dlc/ExpansionPack.h"
#include "util.h"
#include "ConsolePrinter.h"

/*
 * Interpreter entry point
 */
int main() {
    Lexer lexer;
    Parser parser(lexer);
    ConsolePrinter printer;
    Interpreter interpreter(parser, printer);

    ExpansionPack pack;
    pack.install(lexer, parser, interpreter);

    // TODO: read from command line
    std::string text = read_file("../src/main.cpp");
    text = "int main() { return 1 - 20 * 300 + 100 / 10 + 5 % 2; }"; // -5988

    lexer.set_text(text);
    interpreter.run();

    return 0;
}
