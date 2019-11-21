set(EXE_NAME cxx_creed)

set(EXE_SOURCES
        main.cpp
        util.cpp
        util.h

        dlc/ExpansionPack.cpp
        dlc/ExpansionPack.h
        dlc/InterpreterDLC.h
        dlc/LexerDLC.h
        dlc/ParserDLC.h
        dlc/WithDLC.h

        interpreter/Interpreter.cpp
        interpreter/Interpreter.h

        lexer/Lexer.cpp
        lexer/Lexer.h
        lexer/Token.h

        parser/ASTEvent.h
        parser/EOFEvent.cpp
        parser/EOFEvent.h
        parser/EventVisitor.h
        parser/Parser.cpp
        parser/Parser.h
        parser/UnknownTokenEvent.cpp
        parser/UnknownTokenEvent.h
        parser/UnknownTokenTypeEvent.cpp
        parser/UnknownTokenTypeEvent.h
)

add_executable(${EXE_NAME} ${EXE_SOURCES})
