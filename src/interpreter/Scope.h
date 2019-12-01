#pragma once

#include <unordered_map>
#include <string>

class Scope {
public:
    int get(const std::string& key) const;
    bool has_name(const std::string& key) const;
    void set(const std::string& key, int val);

private:
    std::unordered_map<std::string, int> _scope;
};
