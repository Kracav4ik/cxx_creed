#include "TokenList.h"

#include <algorithm>

TokenList::TokenList(std::vector<std::string> token_types) : token_types(std::move(token_types)) {}

bool TokenList::has_token_type(const std::string& token_type) const {
    return std::find(token_types.begin(), token_types.end(), token_type) != token_types.end();
}
