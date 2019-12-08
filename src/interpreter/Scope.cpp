#include "Scope.h"

#include <utility>

int Scope::get(const std::string& key) const {
    auto it = _scope.find(key);
    if (it == _scope.end()) {
        if (_parent) {
            return _parent->get(key);
        }
        return 0;  // TODO: should be "undefined"
    }
    return it->second;
}

void Scope::set_value(const std::string& key, int val) {
    if (has_name_local(key)) {
        _scope[key] = val;
    } else if (_parent && _parent->has_name(key)) {
        _parent->set_value(key, val);
    } else {
        // TODO: scope should have BOTH "declared" status and value for variable names
        // currently "declared" is checked by has_name() call in Evaluator before assignment
        _scope[key] = val;
    }
}

void Scope::create_value(const std::string& key) {
    _scope[key] = 0;  // TODO: should be "uninitialized"
}

bool Scope::has_name(const std::string& key) const {
    return has_name_local(key) || (_parent && _parent->has_name(key));
}

bool Scope::has_name_local(const std::string& key) const {
    return _scope.count(key) > 0;
}

void Scope::set_parent(std::shared_ptr<Scope> scope) {
    _parent = std::move(scope);
}

const std::shared_ptr<Scope>& Scope::get_parent() {
    return _parent;
}
