#pragma once

#include "ASTEvent.h"
#include "string"


struct VarDeclEvent : public ASTEvent {
    VarDeclEvent(std::string type_name, std::string var_name);
    void visit(EventVisitor& visitor) override;

    std::string type_name;
    std::string var_name;
};
