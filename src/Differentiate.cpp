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

template <typename T>
[[nodiscard]] auto Differentiate::Simplify(std::unique_ptr<Expression> expr) const -> std::unique_ptr<Expression>
{
    return this->Copy();
}

} // Oasis