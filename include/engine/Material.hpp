/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Material
*/

#ifndef MATERIAL_HPP_
# define MATERIAL_HPP_

# include <array>
# include "engine/Color.hpp"

namespace nd {
namespace engine {

struct Material {

    Material() = default;

    Material(float refractive_index, const std::array<float, 4> &albedo, const Color &color, float specular_exponent) :
        m_refractive_index  (refractive_index),
        m_specular_exponent (specular_exponent),
        m_diffuse_color     (color),
        m_albedo            (albedo)
    { }

    float m_refractive_index;
    float m_specular_exponent;

    Color m_diffuse_color = White;

    std::array<float, 4> m_albedo;

};

} // namespace engine
} // namespace nd

#endif /* !MATERIAL_HPP_ */
