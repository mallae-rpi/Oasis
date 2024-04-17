//
// Created by Eric Malla on 2/11/24.
//

#include "Oasis/Differentiate.hpp"
#include "Differentiate.hpp"

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
    auto derivative_augend = augend.Differentiate();
    auto derivative_addend = addend.Differentiate();
    return std::make_unique<Add>(std::move(derivative_augend), std::move(derivative_addend));
}

[[nodiscard]] auto Differentiate<Expression>::DifferentiateDifference(const Expression& minuend, const Expression& subtrahend) const -> std::unique_ptr<Expression>
{
    auto derivative_minuend = minuend.Differentiate();
    auto derivative_subtrahend = subtrahend.Differentiate();
    return std::make_unique<Subtract>(std::move(derivative_minuend), std::move(derivative_subtrahend));
}

template <typename CoefficientT, typename ExpressionT>
[[nodiscard]] auto Differentiate<Expression>::DifferentiateConstantMultiple(const CoefficientT& coefficient, const ExpressionT& expression) const -> std::unique_ptr<Expression>
{
    // Differentiate the inner expression
    auto derivative_expression = expression.Differentiate();

    // Multiply the derivative of the inner expression by the constant coefficient
    auto multiplied_derivative = std::make_unique<Multiply>(coefficient.Copy(), std::move(derivative_expression));

    return multiplied_derivative;
}

template <typename Factor1T, typename Factor2T>
auto Differentiate<Expression>::DifferentiateProduct(const Factor1T& factor1, const Factor2T& factor2) const -> std::unique_ptr<Expression>
{
    // Differentiate both factors
    auto derivative_factor1 = factor1.Differentiate();
    auto derivative_factor2 = factor2.Differentiate();

    // Create expressions for the product and its derivatives
    auto product = std::make_unique<Multiply>(factor1.Copy(), factor2.Copy());
    auto product_derivative_factor1 = std::make_unique<Multiply>(derivative_factor1->Copy(), factor2.Copy());
    auto product_derivative_factor2 = std::make_unique<Multiply>(factor1.Copy(), derivative_factor2->Copy());

    // Create an expression for the sum of the products of the derivatives
    auto sum_of_products = std::make_unique<Add>(std::move(product_derivative_factor1), std::move(product_derivative_factor2));

    // Combine the original product and the sum of the products of the derivatives
    auto result = std::make_unique<Add>(std::move(product), std::move(sum_of_products));

    return result;
}

template<typename DividendT, typename DivisorT>
auto Differentiate<Expression>::DifferentiateQuotient(const DividendT & dividend, const DivisorT & divisor) const -> std::unique_ptr<Expression>
{
    // Differentiate the dividend and divisor
    auto d_dividend = dividend.Differentiate();
    auto d_divisor = divisor.Differentiate();

    // Compute the numerator and denominator of the derivative
    auto numerator = MakeExpression<Subtract>(MakeExpression<Multiply>(divisor, std::move(d_dividend)),
        MakeExpression<Multiply>(dividend, std::move(d_divisor)));
    auto denominator = MakeExpression<Exponent>(std::move(d_divisor), MakeExpression<Real>(2.0));

    // Create the quotient expression
    auto result = MakeExpression<Divide>(std::move(numerator), std::move(denominator));

    return result;
}

template <typename OuterFunctionT, typename InnerFunctionT>
auto Differentiate<Expression>::DifferentiateChain(const OuterFunctionT& outer_function, const InnerFunctionT& inner_function) const -> std::unique_ptr<Expression>
{
    // Differentiate the outer and inner functions
    auto d_outer = outer_function.Differentiate();
    auto d_inner = inner_function.Differentiate();

    // Compute the chain rule derivative
    auto result = MakeExpression<Multiply>(std::move(d_outer), std::move(d_inner));

    return result;
}

template <typename T>
[[nodiscard]] auto Differentiate::Simplify(std::unique_ptr<Expression> expr) const -> std::unique_ptr<Expression>
{
    return this->Copy();
}

} // Oasis