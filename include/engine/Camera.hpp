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
# include "engine/math/Rect.hpp"

namespace nd {
namespace engine {

class Camera {
public:
    using ViewPort = math::Rect<unsigned int>;

    Camera(math::Vector3f position, math::Vector3f orientation, ViewPort viewport, float fov = 90.0f);
    ~Camera() = default;

    math::Ray generateRay(float x, float y) const noexcept;

    void onEvent(const SDL_Event &e);
    void onUpdate(decltype(SDL_GetTicks()) dt);

    inline const ViewPort &getViewPort() const noexcept
        { return m_viewport; }

protected:
private:

    float m_fov;
    ViewPort m_viewport;

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
