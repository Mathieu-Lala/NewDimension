/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Scene
*/

#ifndef SCENE_HPP_
# define SCENE_HPP_

# include <memory>
# include "engine/Camera.hpp"

namespace nd {
namespace engine {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    inline void setCamera(std::unique_ptr<Camera> &&cam) noexcept
        { m_camera = std::move(cam); }

    const std::unique_ptr<Camera> &getCamera() const noexcept
        { return m_camera; }

    void onEvent(const SDL_Event &e);
    void onUpdate(decltype(SDL_GetTicks()) dt);

protected:
private:

    // todo : add multiple camera
    std::unique_ptr<Camera> m_camera;

};

} // namespace engine
} // namespace nd

#endif /* !SCENE_HPP_ */
