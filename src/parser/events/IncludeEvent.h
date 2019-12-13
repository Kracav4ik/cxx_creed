#pragma once

#include "ASTEvent.h"
#include <string>

struct IncludeEvent : public ASTEvent {
public:
    explicit IncludeEvent(std::string include);
    void visit(EventVisitor& visitor) override;

    std::string include;
};
