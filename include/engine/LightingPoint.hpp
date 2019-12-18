/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** LightingPoint
*/

#ifndef LIGHTINGPOINT_HPP_
# define LIGHTINGPOINT_HPP_

# include "engine/math/Vector3.hpp"

namespace nd {
namespace engine {

struct LightingPoint {

    LightingPoint(const math::Vector3f &pos, float intensity) :
        m_position  (pos),
        m_intensity (intensity)
    { }

    math::Vector3f m_position;
    float m_intensity;

};

} // namespace engine
} // namespace nd

#endif /* !LIGHTINGPOINT_HPP_ */
