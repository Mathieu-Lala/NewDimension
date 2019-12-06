/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Ray
*/

#ifndef RAY_HPP_
# define RAY_HPP_

# include "engine/math/Vector3.hpp"

namespace nd {
namespace engine {
namespace math {

struct Ray {

    Vector3f m_origin;
    Vector3f m_dest;

    float m_t_min, m_t_max;

};

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !RAY_HPP_ */
