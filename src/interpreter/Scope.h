#pragma once

#include <unordered_map>
#include <string>
#include <memory>

class Scope {
public:
    int get(const std::string& key) const;
    bool has_name(const std::string& key) const;
    bool has_name_local(const std::string& key) const;
    void set_value(const std::string& key, int val);
    void create_value(const std::string& key);
    void set_parent(std::shared_ptr<Scope> scope);
    const std::shared_ptr<Scope>& get_parent();

private:
    std::unordered_map<std::string, int> _scope;
    std::shared_ptr<Scope> _parent;
};
