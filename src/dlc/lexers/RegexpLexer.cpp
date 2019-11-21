#include "RegexpLexer.h"

#include <utility>
#include <string>
#include <cassert>

using svmatch = std::match_results<std::string_view::const_iterator>;

ConsumeResult RegexpLexer::try_consume(std::string_view text) {
    size_t size = 0;
    svmatch match;

    if (std::regex_search(text.begin(), text.end(), match, _regex, std::regex_constants::match_continuous)) {
        assert(match.position() == 0);
        auto sub_match = match[0];
        size = sub_match.length();
    }

    return {_type, text.substr(0, size)};
}

RegexpLexer::RegexpLexer(std::string type, std::string regexp) : _type(std::move(type)), _regex(std::move(regexp)) {}
