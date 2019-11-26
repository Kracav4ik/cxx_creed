#pragma once

#include <vector>
#include <string>

struct TokenList {
    explicit TokenList(std::vector<std::string> token_types);

    bool has_token_type(const std::string& token_type) const;

    std::vector<std::string> token_types;
};
