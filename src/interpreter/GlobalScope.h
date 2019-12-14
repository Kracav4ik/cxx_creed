#pragma once

#include "Scope.h"

class GlobalScope : public Scope {
public:
    void insert_type(TypePtr type);

    TypePtr get_type(const std::string& key) const override;
    void set_value(const std::string& key, ValuePtr val) override;
    void create_value(const std::string& key, const TypeBase& val) override;

private:
    std::unordered_map<std::string, TypePtr> _types;
};
