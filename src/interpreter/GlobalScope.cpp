#include "GlobalScope.h"

#include <utility>

#include "interpreter/types/TypeBase.h"

TypePtr GlobalScope::get_type(const std::string& key) const {
    auto it = _types.find(key);
    if (it != _types.end()) {
        return it->second;
    }
    return nullptr;
}

void GlobalScope::insert_type(TypePtr type) {
    std::string type_name = type->type_name();
    _types.emplace(std::move(type_name), std::move(type));
}

void GlobalScope::force_set_value(const std::string& key, ValuePtr val) {
    Scope::set_value(key, std::move(val));
}

void GlobalScope::set_value(const std::string& key, ValuePtr val) {}

void GlobalScope::create_value(const std::string& key, const TypeBase& val) {}
