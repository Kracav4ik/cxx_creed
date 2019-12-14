#pragma once

#include "interpreter/types/ValueFwd.h"

#include <unordered_map>
#include <string>
#include <memory>

class TypeBase;
class Scope {
public:
    ValuePtr get(const std::string& key) const;
    bool has_name(const std::string& key) const;
    bool has_name_local(const std::string& key) const;
    virtual void set_value(const std::string& key, ValuePtr val);
    virtual void create_value(const std::string& key, const TypeBase& val);
    void set_parent(std::shared_ptr<Scope> scope);
    const std::shared_ptr<Scope>& get_parent();

    virtual TypePtr get_type(const std::string& key) const;

    virtual ~Scope() = default;

private:
    std::unordered_map<std::string, ValuePtr> _scope;
    std::shared_ptr<Scope> _parent;
};
