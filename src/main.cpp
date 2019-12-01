#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "interpreter/Interpreter.h"
#include "dlc/ExpansionPack.h"
#include "util.h"
#include "ConsolePrinter.h"

/*
 * Interpreter entry point
 */
int main(int argc, const char* argv[]) {
    Lexer lexer;
    Parser parser(lexer);
    ConsolePrinter printer;
    Interpreter interpreter(parser, printer);

    ExpansionPack pack;
    pack.install(lexer, parser, interpreter);

    {
        std::string text;
        if (argc == 2) {
            text = read_file(argv[1]);
        } else {
            text = "int main() { return 1 - 20 * 300 + 100 / 10 + 5 % 2; }"; // -5988
        }

        lexer.set_text(std::move(text));
    }

    interpreter.run();

    return 0;
}
