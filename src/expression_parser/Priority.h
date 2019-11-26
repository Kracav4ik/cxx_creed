#pragma once

/// see doc/expression.txt
enum class Priority {
    /* there is a priority at the top for the operator "," but it will never be supported, ever */
    ASSIGNMENT_EXPRESSION,       ///< x = y, x *= y, x /= y, x %= y, x += y, x -= y, x >>= y, x <<= y, x &= y, x ˆ= y, x |= y
    CONDITIONAL_EXPRESSION,      ///< x ? y : z
    LOGICAL_OR_EXPRESSION,       ///< x || y
    LOGICAL_AND_EXPRESSION,      ///< x && y
    INCLUSIVE_OR_EXPRESSION,     ///< x | y
    EXCLUSIVE_OR_EXPRESSION,     ///< x ^ y
    AND_EXPRESSION,              ///< x & y
    EQUALITY_EXPRESSION,         ///< x == y, x != y
    RELATIONAL_EXPRESSION,       ///< x < y, x > y, x <= y, x >= y
    SHIFT_EXPRESSION,            ///< x << y, x >> y
    ADDITIVE_EXPRESSION,         ///< x + y, x - y
    MULTIPLICATIVE_EXPRESSION,   ///< x * y, x / y, x % y
    PM_EXPRESSION,               ///< x .* y, x ->* y
    CAST_EXPRESSION,             ///< ( x ) y
    UNARY_EXPRESSION,            ///< ++ x, -- x, * x, & x, + x, - x, ! x, ~ x, new x, delete x, sizeof ( x )
    POSTFIX_EXPRESSION,          ///< x [ y ], x ( a, b, c ), x . y, x -> y, x ++, x --
    PRIMARY_EXPRESSION,          ///< 123, 1.5e-3, "abc", 'x', true, false, this, ( a + b * c ), x
};
