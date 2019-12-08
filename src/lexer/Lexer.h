#pragma once

#include "dlc/WithDLC.h"
#include "dlc/LexerDLC.h"

#include <string>

struct Token;

class Lexer : public WithDLC<LexerDLC> {
public:
    class State {
    friend class Lexer;
    public:
        void drop();
        void revert();
        ~State();

    private:
        explicit State(Lexer& lexer);
        void assign(size_t pos);

        Lexer& _lexer;
        size_t _pos;
        bool _dropped = false;
    };

    void set_text(std::string text);
    State get_state();

    Token next_token(bool skip_space=true);
    void skip_whitespace();
    Token next_token_with_type(const std::string& expected_type);

private:
    std::string consume(size_t amount);
    std::string_view current_text() const;

    std::string _text;
    size_t _pos = 0;
};
