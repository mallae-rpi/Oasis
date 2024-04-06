//
// Created by Eric Malla on 2/11/24.
//

#include "Oasis/Differentiate.hpp"

namespace Oasis {

auto Differentiate<Expression>::ToString() const -> std::string final
{
    return std::string();
}

auto Differentiate<Expression>::DifferentiatePower(const Real& base, const Real& exponent) const -> std::unique_ptr<Expression>
{
    // Differentiate a power function: d(x^n)/dx = n * x^(n-1)
    double n = exponent.GetValue();
    double newExponent = n - 1.0;
    return std::make_unique<Multiply<Real, Real>>(Real(n), std::make_unique<Exponent<Variable, Real>>(Variable("x"), Real(newExponent)));
}

template <typename BaseT, typename PowerT>
auto DifferentiatePower(const BaseT& base, const PowerT& exponent) const -> std::unique_ptr<Expression>
{
    if constexpr (std::is_same<BaseT, Real>::value && std::is_same<PowerT, Real>::value) {
        // If both base and exponent are real numbers, apply the constant rule: d/dx (c^n) = 0
        return std::make_unique<Real>(0.0);
    } else if constexpr (std::is_same<BaseT, Variable>::value && std::is_same<PowerT, Real>::value) {
        // If base is a variable and exponent is a real number, apply the power rule: d/dx (x^n) = n*x^(n-1)
        double n = exponent.GetValue();
        if (n == 0.0) {
            // If exponent is 0, derivative is 0
            return std::make_unique<Real>(0.0);
        } else {
            // Otherwise, apply the power rule
            auto derivative_exponent = std::make_unique<Real>(n - 1.0);
            auto multiplied_exponent = std::make_unique<Multiply>(std::move(derivative_exponent), base.Copy());
            return std::move(multiplied_exponent);
        }
    } else {
        // For more complex expressions, return nullptr for now
        return nullptr;
    }
}

[[nodiscard]] auto Differentiate<Expression>::DifferentiateConstant(double constant) const -> std::unique_ptr<Expression>
{
    return std::make_unique<Real>(0.0);
}

[[nodiscard]] auto Differentiate<Expression>::DifferentiateSum(const Expression& augend, const Expression& addend) const -> std::unique_ptr<Expression>
{
    auto derivative_augend = Differentiate<Expression>().DifferentiateExpression(augend);
    auto derivative_addend = Differentiate<Expression>().DifferentiateExpression(addend);
    return std::make_unique<Add>(std::move(derivative_augend), std::move(derivative_addend));
}

[[nodiscard]] auto Differentiate<Expression>::DifferentiateDifference(const Expression& minuend, const Expression& subtrahend) const -> std::unique_ptr<Expression>
{
    auto derivative_minuend = Differentiate<Expression>().DifferentiateExpression(minuend);
    auto derivative_subtrahend = Differentiate<Expression>().DifferentiateExpression(subtrahend);
    return std::make_unique<Subtract>(std::move(derivative_minuend), std::move(derivative_subtrahend));
}

[[nodiscard]] auto Differentiate<Expression>::DifferentiateExpression(const Expression& expression) const -> std::unique_ptr<Expression>
{
    if (expression.Is<Real>()) {
        return std::make_unique<Real>(0.0);
    } else if (expression.Is<Variable>()) {
        return std::make_unique<Real>(1.0);
    } else if (expression.Is<Add>()) {
        const auto& add_expression = static_cast<const Add&>(expression);
    } else if (expression.Is<Subtract>()) {
        const auto& subtract_expression = static_cast<const Subtract&>(expression);
    } else {
        throw std::runtime_error("Differentiation not implemented for this expression type.");
    }
}

template <typename CoefficientT, typename ExpressionT>
[[nodiscard]] auto Differentiate<Expression>::DifferentiateConstantMultiple(const CoefficientT& coefficient, const ExpressionT& expression) const -> std::unique_ptr<Expression> {
    // Differentiate the inner expression
    auto derivative_expression = expression.Differentiate();

    // Multiply the derivative of the inner expression by the constant coefficient
    auto multiplied_derivative = std::make_unique<Multiply>(coefficient.Copy(), std::move(derivative_expression));

    return multiplied_derivative;
}

template <typename T>
[[nodiscard]] auto Differentiate::Simplify(std::unique_ptr<Expression> expr) const -> std::unique_ptr<Expression>
{
    return this->Copy();
}

} // Oasis