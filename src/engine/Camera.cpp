/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Camera
*/

#include "engine/Camera.hpp"
#include "engine/math/function.hpp"

#include "engine/Logger.hpp"

nd::engine::Camera::Camera(
    math::Vector3f position,
    math::Vector3f orientation,
    ViewPort viewport,
    float fov) :

    m_fov       (fov),
    m_viewport  (std::move(viewport)),

    m_position              (std::move(position)),
    m_deplacement_momentum  (0.0f),
    m_deplacement_speed     (0.1f, 0.1f, 0.1f),

    m_orientation           (std::move(orientation)),
    m_rotation_momentum     (0.0f),
    m_rotation_sensibility  (0.05f, 0.05f, 0.05f)
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

void nd::engine::Camera::onEvent(const SDL_Event &e)
{
    // todo : not hardcode the key

    if (e.type == SDL_KEYDOWN) {

        // RESET CAMERA

        if (e.key.keysym.scancode == SDL_SCANCODE_KP_ENTER) {
            this->m_position = { 0.0f };
            this->m_deplacement_momentum = { 0.0f };

            this->m_orientation = { 0.0f, 0.0f, 1.0f };
            this->m_rotation_momentum = { 0.0f };
            return;
        }

        // DEPLACEMENT

        if (e.key.keysym.scancode == SDL_SCANCODE_W)
            m_deplacement_momentum += m_orientation.getForwardVector();
        else if (e.key.keysym.scancode == SDL_SCANCODE_S)
            m_deplacement_momentum += m_orientation.getForwardVector() * -1.0f;

        if (e.key.keysym.scancode == SDL_SCANCODE_A)
            m_deplacement_momentum += m_orientation.getRightVector() * -1.0f;
        else if (e.key.keysym.scancode == SDL_SCANCODE_D)
            m_deplacement_momentum += m_orientation.getRightVector();

        if (e.key.keysym.scancode == SDL_SCANCODE_R)
            m_deplacement_momentum += m_orientation.getUpVector() * -1.0f;
        else if (e.key.keysym.scancode == SDL_SCANCODE_F)
            m_deplacement_momentum += m_orientation.getUpVector();

        // FOV

//#define DEBUG_FOV
        if (e.key.keysym.scancode == SDL_SCANCODE_B) {
            m_fov += 3.0f;
#ifdef DEBUG_FOV
            DEBUG("Camera:: Fov set to: " << m_fov);
#endif
        } else if (e.key.keysym.scancode == SDL_SCANCODE_N) {
            m_fov -= 3.0f;
#ifdef DEBUG_FOV
            DEBUG("Camera:: Fov set to: " << m_fov);
#endif
        }

        // ORIENTATION

        if (e.key.keysym.scancode == SDL_SCANCODE_UP)
            m_rotation_momentum += m_orientation.getRightVector();
        else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
            m_rotation_momentum += m_orientation.getRightVector() * -1.0f;

        if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
            m_rotation_momentum += m_orientation.getUpVector() * -1.0f;
        else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
            m_rotation_momentum += m_orientation.getUpVector();

        if (e.key.keysym.scancode == SDL_SCANCODE_Q)
            m_rotation_momentum += m_orientation.getForwardVector();
        else if (e.key.keysym.scancode == SDL_SCANCODE_E)
            m_rotation_momentum += m_orientation.getForwardVector() * -1.0f;

    } else if (e.type == SDL_KEYUP) {

        // RESET DEPLACEMENT MOMENTUM

        if (e.key.keysym.scancode == SDL_SCANCODE_W)
            m_deplacement_momentum = { 0.0f };
        else if (e.key.keysym.scancode == SDL_SCANCODE_S)
            m_deplacement_momentum = { 0.0f };

        if (e.key.keysym.scancode == SDL_SCANCODE_A)
            m_deplacement_momentum = { 0.0f };
        else if (e.key.keysym.scancode == SDL_SCANCODE_D)
            m_deplacement_momentum = { 0.0f };

        if (e.key.keysym.scancode == SDL_SCANCODE_R)
            m_deplacement_momentum = { 0.0f };
        else if (e.key.keysym.scancode == SDL_SCANCODE_F)
            m_deplacement_momentum = { 0.0f };

        // RESET ROTATION MOMENTUM

        if (e.key.keysym.scancode == SDL_SCANCODE_UP)
            m_rotation_momentum = { 0.0f };
        else if (e.key.keysym.scancode == SDL_SCANCODE_DOWN)
            m_rotation_momentum = { 0.0f };

        if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
            m_rotation_momentum = { 0.0f };
        else if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
            m_rotation_momentum = { 0.0f };

        if (e.key.keysym.scancode == SDL_SCANCODE_Q)
            m_rotation_momentum = { 0.0f };
        else if (e.key.keysym.scancode == SDL_SCANCODE_E)
            m_rotation_momentum = { 0.0f };

    }

}

void nd::engine::Camera::onUpdate(decltype(SDL_GetTicks()) dt)
{
    if (m_deplacement_momentum != math::Vector3f { 0.0f }) {
        this->m_position += m_deplacement_momentum.mult_coord(m_deplacement_speed) * dt;
//#define DEBUG_POSITION
#ifdef DEBUG_POSITION
        DEBUG("Camera:: New position: (" <<
            this->m_position.x << ", " <<
            this->m_position.y << ", " <<
            this->m_position.z << ")");
        DEBUG("Camera:: With deplacement momentum: (" <<
            this->m_deplacement_momentum.x << ", " <<
            this->m_deplacement_momentum.y << ", " <<
            this->m_deplacement_momentum.z << ")");
#endif
    }

    if (m_rotation_momentum != math::Vector3f { 0.0f }) {
        m_orientation = (m_rotation_momentum.euler(dt).mult_coord(m_rotation_sensibility) * m_orientation).normalize();
//#define DEBUG_ORIENTATION
#ifdef DEBUG_ORIENTATION
        DEBUG("Camera:: New orientation: (" <<
            this->m_orientation.x << ", " <<
            this->m_orientation.y << ", " <<
            this->m_orientation.z << ")");
        DEBUG("Camera:: With rotation momentum: (" <<
            this->m_rotation_momentum.x << ", " <<
            this->m_rotation_momentum.y << ", " <<
            this->m_rotation_momentum.z << ")");
#endif
    }
}
