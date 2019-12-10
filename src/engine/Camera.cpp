/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Camera
*/

#include "engine/Camera.hpp"
#include "engine/math/function.hpp"

nd::engine::Camera::Camera(math::Vector3f position, math::Vector3f orientation, float fov) :
    m_position      (std::move(position)),
    m_orientation   (std::move(orientation)),
    m_fov           (fov)
{ }

nd::engine::math::Ray nd::engine::Camera::generateRay(float x, float y) const noexcept
{
    return math::Ray {
        this->m_position,
        m_orientation *
            math::Vector3f(x * math::degree2rad(m_fov), y * math::degree2rad(m_fov), 1.0f) *
            m_orientation.conjugate()
    };
}
