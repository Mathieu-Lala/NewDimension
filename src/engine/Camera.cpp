/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Camera
*/

#include "engine/Camera.hpp"

nd::engine::Camera::Camera(math::Vector3f position, math::Vector3f orientation, float fov) :
    m_position      (std::move(position)),
    m_orientation   (std::move(orientation)),
    m_fov           (fov)
{ }

void nd::engine::Camera::generateRay(float x, float y, math::Ray &ray)
{
    // todo : implement fov

    ray.m_origin = this->m_position;
    ray.m_dest = m_orientation * math::Vector3f(x, y, 1.0f) * m_orientation.conjugate();
}
