#include "ExpressionParserDLC.h"

ExpressionParserDLC::ExpressionParserDLC(Priority priority) : _priority(priority) {}

Priority ExpressionParserDLC::getPriority() const {
    return _priority;
}
