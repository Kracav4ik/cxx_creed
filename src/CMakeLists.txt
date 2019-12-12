set(EXE_NAME cxx_creed)

set(EXE_SOURCES
        main.cpp
)

set(LIB_SOURCES
        ConsolePrinter.cpp
        ConsolePrinter.h
        Printer.h
        util.cpp
        util.h

        dlc/ExpansionPack.cpp
        dlc/ExpansionPack.h
        dlc/ExpressionParserDLC.cpp
        dlc/ExpressionParserDLC.h
        dlc/InterpreterDLC.h
        dlc/LexerDLC.h
        dlc/ParserDLC.h
        dlc/WithDLC.h

        dlc/expression_parsers/AssignmentParser.cpp
        dlc/expression_parsers/AssignmentParser.h
        dlc/expression_parsers/BinaryOpParser.cpp
        dlc/expression_parsers/BinaryOpParser.h
        dlc/expression_parsers/IntegerParser.cpp
        dlc/expression_parsers/IntegerParser.h
        dlc/expression_parsers/ParensParser.cpp
        dlc/expression_parsers/ParensParser.h
        dlc/expression_parsers/UnaryOpParser.cpp
        dlc/expression_parsers/UnaryOpParser.h
        dlc/expression_parsers/VariableParser.cpp
        dlc/expression_parsers/VariableParser.h

        dlc/lexers/BlockCommentLexer.cpp
        dlc/lexers/BlockCommentLexer.h
        dlc/lexers/ExactLexer.cpp
        dlc/lexers/ExactLexer.h
        dlc/lexers/IdentifierLexer.cpp
        dlc/lexers/IdentifierLexer.h
        dlc/lexers/IntegerLexer.cpp
        dlc/lexers/IntegerLexer.h
        dlc/lexers/LineCommentLexer.cpp
        dlc/lexers/LineCommentLexer.h
        dlc/lexers/RegexpLexer.cpp
        dlc/lexers/RegexpLexer.h
        dlc/lexers/NewlineLexer.cpp
        dlc/lexers/NewlineLexer.h
        dlc/lexers/WhitespaceLexer.cpp
        dlc/lexers/WhitespaceLexer.h

        expression_parser/ASTVisitor.h
        expression_parser/ExpressionParser.cpp
        expression_parser/ExpressionParser.h
        expression_parser/Priority.h
        expression_parser/TokenList.cpp
        expression_parser/TokenList.h

        expression_parser/ast/AssignmentNode.cpp
        expression_parser/ast/AssignmentNode.h
        expression_parser/ast/ASTNode.h
        expression_parser/ast/BinaryOpNode.cpp
        expression_parser/ast/BinaryOpNode.h
        expression_parser/ast/IntegerNode.cpp
        expression_parser/ast/IntegerNode.h
        expression_parser/ast/UnaryOpNode.cpp
        expression_parser/ast/UnaryOpNode.h
        expression_parser/ast/VariableNode.cpp
        expression_parser/ast/VariableNode.h

        interpreter/exceptions/ArithmeticException.cpp
        interpreter/exceptions/ArithmeticException.h
        interpreter/exceptions/OperandTypeException.cpp
        interpreter/exceptions/OperandTypeException.h
        interpreter/exceptions/RuntimeException.cpp
        interpreter/exceptions/RuntimeException.h
        interpreter/exceptions/UnknownOpException.cpp
        interpreter/exceptions/UnknownOpException.h

        interpreter/types/IntegerType.cpp
        interpreter/types/IntegerType.h
        interpreter/types/IntegerValue.cpp
        interpreter/types/IntegerValue.h
        interpreter/types/RealTypeBase.h
        interpreter/types/RealTypeBase.hpp
        interpreter/types/RealValueBase.h
        interpreter/types/RealValueBase.hpp
        interpreter/types/TypeBase.h
        interpreter/types/ValueBase.h
        interpreter/types/ValueFwd.h

        interpreter/Evaluator.cpp
        interpreter/Evaluator.h
        interpreter/Interpreter.cpp
        interpreter/Interpreter.h
        interpreter/InterpreterBase.cpp
        interpreter/InterpreterBase.h
        interpreter/Scope.cpp
        interpreter/Scope.h

        lexer/Lexer.cpp
        lexer/Lexer.h
        lexer/Token.h

        parser/CachingParser.cpp
        parser/CachingParser.h
        parser/EventVisitor.h
        parser/EventVisitorAdapter.h
        parser/Parser.cpp
        parser/Parser.h
        parser/ParserBase.h

        parser/events/ASTEvent.h
        parser/events/BeginBlockStmtEvent.cpp
        parser/events/BeginBlockStmtEvent.h
        parser/events/BeginIfStmtEvent.cpp
        parser/events/BeginIfStmtEvent.h
        parser/events/BeginMainDeclEvent.cpp
        parser/events/BeginMainDeclEvent.h
        parser/events/BeginWhileStmtEvent.cpp
        parser/events/BeginWhileStmtEvent.h
        parser/events/EndBlockStmtEvent.cpp
        parser/events/EndBlockStmtEvent.h
        parser/events/EndIfStmtEvent.cpp
        parser/events/EndIfStmtEvent.h
        parser/events/EndMainDeclEvent.cpp
        parser/events/EndMainDeclEvent.h
        parser/events/EndWhileStmtEvent.cpp
        parser/events/EndWhileStmtEvent.h
        parser/events/EOFEvent.cpp
        parser/events/EOFEvent.h
        parser/events/ExprStmtEvent.cpp
        parser/events/ExprStmtEvent.h
        parser/events/ParseErrorEvent.cpp
        parser/events/ParseErrorEvent.h
        parser/events/ReturnStmtEvent.cpp
        parser/events/ReturnStmtEvent.h
        parser/events/UnknownTokenEvent.cpp
        parser/events/UnknownTokenEvent.h
        parser/events/UnknownTokenTypeEvent.cpp
        parser/events/UnknownTokenTypeEvent.h
        parser/events/VarDeclEvent.cpp
        parser/events/VarDeclEvent.h

        parser/miniparsers/BlockMiniparser.cpp
        parser/miniparsers/BlockMiniparser.h
        parser/miniparsers/IfMiniparser.cpp
        parser/miniparsers/IfMiniparser.h
        parser/miniparsers/MainMiniparser.cpp
        parser/miniparsers/MainMiniparser.h
        parser/miniparsers/Miniparser.cpp
        parser/miniparsers/Miniparser.h
        parser/miniparsers/WhileMiniparser.cpp
        parser/miniparsers/WhileMiniparser.h
)

add_executable(${EXE_NAME} ${EXE_SOURCES})
add_library(creed_common STATIC ${LIB_SOURCES})
target_link_libraries(cxx_creed creed_common)
