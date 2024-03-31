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
[[nodiscard]] auto Differentiate<Expression>::DifferentiatePower(const BaseT& base, const PowerT& exponent) const -> std::unique_ptr<Expression>
{
    // Applying the Power Rule: d/dx(x^n) = n * x^(n-1)
    auto new_exponent = std::make_unique<Subtract<PowerT>>();
    new_exponent->SetMostSigOp(exponent.Copy());
    new_exponent->SetLeastSigOp(std::make_unique<Real>(1.0));

    auto new_coefficient = std::make_unique<Multiply<PowerT>>();
    new_coefficient->SetMostSigOp(exponent.Copy());
    new_coefficient->SetLeastSigOp(base.Copy());

    auto derivative = std::make_unique<Multiply<Multiply<PowerT>, BaseT>>();
    derivative->SetMostSigOp(std::move(new_coefficient));
    derivative->SetLeastSigOp(std::move(new_exponent));

    return derivative;
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

template <typename T>
[[nodiscard]] auto Differentiate::Simplify(std::unique_ptr<Expression> expr) const -> std::unique_ptr<Expression>
{
    return this->Copy();
}

} // Oasis