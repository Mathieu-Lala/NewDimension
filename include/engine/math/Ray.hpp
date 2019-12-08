/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Ray
*/

#ifndef RAY_HPP_
# define RAY_HPP_

# include <utility>
# include "engine/math/Vector3.hpp"

namespace nd {
namespace engine {
namespace math {

struct Ray {

    constexpr Ray() :
        m_t_min (0.001f),
        m_t_max (1000.0f)
    { }

    constexpr Ray(Vector3f origin, Vector3f dest, float t_min = 0.001f, float t_max = 1000.0f) :
        m_origin    (std::move(origin)),
        m_dest      (std::move(dest)),
        m_t_min     (t_min),
        m_t_max     (t_max)
    { }

    ~Ray() = default;

    Vector3f m_origin;
    Vector3f m_dest;

    float m_t_min;
    float m_t_max;

};

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !RAY_HPP_ */
