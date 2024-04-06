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

    // Differentiate the power of a real base with a real exponent.
    // Specialized for real numbers.
    [[nodiscard]] auto DifferentiatePower(const Real& base, const Real& exponent) const -> std::unique_ptr<Expression>;

    // Differentiate the power of a base with an exponent.
    // Templated and can handle differentiation of expressions involving arbitrary types.
    template <typename BaseT, typename PowerT>
    [[nodiscard]] auto DifferentiatePower(const BaseT& base, const PowerT& exponent) const -> std::unique_ptr<Expression>;

    // Differentiate a constant value.
    [[nodiscard]] auto DifferentiateConstant(double constant) const -> std::unique_ptr<Expression>;

    // Differentiate the sum of two expressions.
    [[nodiscard]] auto DifferentiateSum(const Expression& augend, const Expression& addend) const -> std::unique_ptr<Expression>;

    // Differentiate the difference of two expressions.
    [[nodiscard]] auto DifferentiateDifference(const Expression& minuend, const Expression& subtrahend) const -> std::unique_ptr<Expression>;

    // Helper function for simplifying expressions
    template <typename T>
    [[nodiscard]] auto Simplify(std::unique_ptr<Expression> expr) const -> std::unique_ptr<Expression>;

private:
    // Function to differentiate an expression.
    [[nodiscard]] auto DifferentiateExpression(const Expression& expression) const -> std::unique_ptr<Expression>;
}

} // Oasis

#endif // OASIS_DIFFERENTIATE_HPP
