//
// Created by Eric Malla on 2/11/24.
//

#ifndef OASIS_DIFFERENTIATE_HPP
#define OASIS_DIFFERENTIATE_HPP

#include "Expression.hpp"
#include "LeafExpression.hpp"
#include "Real.hpp"
#include "Variable.hpp"

namespace Oasis {

template <IExpression ExpressionT>
class Differentiate;

/// @cond
template <>
class Differentiate<Expression> : public LeafExpression<Differentiate> {
public:
    Differentiate() = default;
    Differentiate(const Differentiate& other) = default;

    EXPRESSION_TYPE(Differentiate);

    [[nodiscard]] auto ToString() const -> std::string final;
}

} // Oasis

#endif // OASIS_DIFFERENTIATE_HPP
