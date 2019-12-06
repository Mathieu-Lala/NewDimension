/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** function
*/

#ifndef FUNCTION_HPP_
# define FUNCTION_HPP_

# include <cmath>
# include "engine/math/Vector3.hpp"

namespace nd {
namespace engine {
namespace math {

// resolve the mathematical function: f(x) = ax^2 + bx + c
constexpr bool solveQuadratic(
    // input
    const float a, const float b, const float c,
    // ouput
    float &x0, float &x1)
{
    auto discr = std::pow(b, 2) - 4 * a * c;

    if (discr < 0)
        return false;
    else if (discr == 0) {
        x0 = - 0.5 * b / a;
        x1 = - 0.5 * b / a;
    } else {
        auto q = (b > 0) ?
            -0.5 * (b + std::sqrt(discr)) :
            -0.5 * (b - std::sqrt(discr));
        x0 = q / a;
        x1 = c / q;
    }

    if (x0 > x1)
        std::swap(x0, x1);

    return true;
}

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !FUNCTION_HPP_ */
