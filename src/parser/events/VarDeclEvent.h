#pragma once

#include "ASTEvent.h"
#include "string"


struct VarDeclEvent : public ASTEvent {
    explicit VarDeclEvent(std::string value);
    void visit(EventVisitor& visitor) override;

    std::string var_name;
};
