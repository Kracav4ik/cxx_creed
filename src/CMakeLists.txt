set(EXE_NAME cxx_creed)

set(EXE_SOURCES
        main.cpp
)

set(LIB_SOURCES
        util.cpp
        util.h

        dlc/ExpansionPack.cpp
        dlc/ExpansionPack.h
        dlc/InterpreterDLC.h
        dlc/LexerDLC.h
        dlc/ParserDLC.h
        dlc/WithDLC.h

        dlc/lexers/ExactLexer.cpp
        dlc/lexers/ExactLexer.h
        dlc/lexers/IdentifierLexer.cpp
        dlc/lexers/IdentifierLexer.h
        dlc/lexers/IntegerLexer.cpp
        dlc/lexers/IntegerLexer.h
        dlc/lexers/RegexpLexer.cpp
        dlc/lexers/RegexpLexer.h
        dlc/lexers/NewlineLexer.cpp
        dlc/lexers/NewlineLexer.h
        dlc/lexers/WhitespaceLexer.cpp
        dlc/lexers/WhitespaceLexer.h

        interpreter/Interpreter.cpp
        interpreter/Interpreter.h
        interpreter/InterpreterBase.cpp
        interpreter/InterpreterBase.h

        lexer/Lexer.cpp
        lexer/Lexer.h
        lexer/Token.h

        parser/ASTEvent.h
        parser/BeginMainDeclEvent.cpp
        parser/BeginMainDeclEvent.h
        parser/EndMainDeclEvent.cpp
        parser/EndMainDeclEvent.h
        parser/EOFEvent.cpp
        parser/EOFEvent.h
        parser/EventVisitor.h
        parser/EventVisitorAdapter.h
        parser/ParseErrorEvent.cpp
        parser/ParseErrorEvent.h
        parser/Parser.cpp
        parser/Parser.h
        parser/ReturnStmtEvent.cpp
        parser/ReturnStmtEvent.h
        parser/UnknownTokenEvent.cpp
        parser/UnknownTokenEvent.h
        parser/UnknownTokenTypeEvent.cpp
        parser/UnknownTokenTypeEvent.h
)

add_executable(${EXE_NAME} ${EXE_SOURCES})
add_library(creed_common STATIC ${LIB_SOURCES})
target_link_libraries(cxx_creed creed_common)
