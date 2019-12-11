/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Scene
*/

#ifndef SCENE_HPP_
# define SCENE_HPP_

# include <memory>
# include <list>
# include "engine/Camera.hpp"

namespace nd {
namespace engine {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    nd::engine::Camera *addCamera(std::unique_ptr<Camera> &&cam) noexcept;

    const std::list<std::unique_ptr<Camera>> &getCameras() const noexcept;

    void onEvent(const SDL_Event &e);
    void onUpdate(decltype(SDL_GetTicks()) dt);

protected:
private:

    std::list<std::unique_ptr<Camera>> m_cameras;

};

} // namespace engine
} // namespace nd

#endif /* !SCENE_HPP_ */
