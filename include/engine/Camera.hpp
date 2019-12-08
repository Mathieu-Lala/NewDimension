/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include "engine/math/Vector3.hpp"
# include "engine/math/Ray.hpp"

namespace nd {
namespace engine {

class Camera {
public:
    Camera(math::Vector3f position, math::Vector3f orientation, float fov = 90.0f);
    ~Camera() = default;

    void generateRay(float x, float y, math::Ray &ray);

protected:
private:

    math::Vector3f m_position;
    math::Vector3f m_orientation;
    float m_fov;

};

} // namespace engine
} // namespace nd

#endif /* !CAMERA_HPP_ */
