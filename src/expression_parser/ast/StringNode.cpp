#include "StringNode.h"

#include "expression_parser/ASTVisitor.h"

#include <sstream>
#include <unordered_map>
#include <cassert>

StringNode::StringNode(std::string raw_value) : raw_value(std::move(raw_value)) {}

void StringNode::visit(ASTVisitor& visitor) const {
    visitor.visitString(*this);
}

std::string StringNode::value() const {
    // raw_value is text with escapes and double quotes
    assert(raw_value.size() >= 2);
    std::stringstream result;
    for (size_t i = 1; i + 1 < raw_value.size(); ++i) {
        if (raw_value[i] == '\\') {
            ++i;
            assert(i + 1 < raw_value.size());
            static std::unordered_map<char, char> escapes = {
                    {'0', '\0'},
                    {'a', '\a'},
                    {'b', '\b'},
                    {'f', '\f'},
                    {'n', '\n'},
                    {'r', '\r'},
                    {'t', '\t'},
                    {'v', '\v'},
            };
            auto it = escapes.find(raw_value[i]);
            if (it != escapes.end()) {
                result << it->second;
                continue;
            }
        }
        result << raw_value[i];
    }
    return result.str();
}
