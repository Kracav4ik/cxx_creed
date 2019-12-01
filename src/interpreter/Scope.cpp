#include "Scope.h"

int Scope::get(const std::string& key) const {
    auto it = _scope.find(key);
    if (it == _scope.end()) {
        return 0;
    }
    return it->second;
}

void Scope::set(const std::string& key, int val) {
    _scope[key] = val;
}

bool Scope::has_name(const std::string& key) const {
    return _scope.count(key) > 0;
}
