#include "InterpreterChecker.h"

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "interpreter/Interpreter.h"
#include "dlc/ExpansionPack.h"
#include "TestPrinter.h"
#include <utility>

InterpreterChecker::InterpreterChecker(std::string code) {
    Lexer lexer;
    Parser parser(lexer);
    TestPrinter printer;
    Interpreter interpreter(parser, printer);

    ExpansionPack pack;
    pack.install(lexer, parser, interpreter);

    lexer.set_text(std::move(code));

    interpreter.run();
    _output = printer.str();
}

const std::string& InterpreterChecker::output() const {
    return _output;
}
