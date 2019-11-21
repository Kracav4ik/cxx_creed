#include "NewlineLexer.h"

ConsumeResult NewlineLexer::try_consume(std::string_view text) {
    size_t size = 0;
    if (!text.empty() && text[0] == '\n') {
        size = 1;
    }

    return {"NEWLINE", text.substr(0, size)};
}
