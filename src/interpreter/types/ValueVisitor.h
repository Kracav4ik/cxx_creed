#pragma once

class IntegerValue;
class StringValue;

class ValueVisitor {
public:
    virtual void visitIntegerValue(IntegerValue& value) = 0;
    virtual void visitStringValue(StringValue& value) = 0;

    virtual ~ValueVisitor() = default;
};
