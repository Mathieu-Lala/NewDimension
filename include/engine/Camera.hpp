/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
# define CAMERA_HPP_

# include <SDL2/SDL.h>
# include "engine/math/Vector3.hpp"
# include "engine/math/Ray.hpp"

namespace nd {
namespace engine {

class Camera {
public:
    Camera(math::Vector3f position, math::Vector3f orientation, float fov = 90.0f);
    ~Camera() = default;

    math::Ray generateRay(float x, float y) const noexcept;

    void onEvent(const SDL_Event &e);
    void onUpdate(decltype(SDL_GetTicks()) dt);

protected:
private:

    float m_fov;

    // todo : add view port on window

    // the data under should be in a 'transform' class

    math::Vector3f m_position;
    math::Vector3f m_deplacement_momentum;
    math::Vector3f m_deplacement_speed;

    math::Vector3f m_orientation;
    math::Vector3f m_rotation_momentum;
    math::Vector3f m_rotation_sensibility;

};

} // namespace engine
} // namespace nd

#endif /* !CAMERA_HPP_ */
