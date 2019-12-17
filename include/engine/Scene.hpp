/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Scene
*/

#ifndef SCENE_HPP_
# define SCENE_HPP_

# include <memory>
# include <vector>
# include "engine/Camera.hpp"
# include "engine/TimeManager.hpp"

namespace nd {
namespace engine {

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    using Cameras = std::vector<std::unique_ptr<Camera>>;

    nd::engine::Camera *addCamera(std::unique_ptr<Camera> &&cam) noexcept;

    const Cameras &getCameras() const noexcept;

    virtual void onEvent(const SDL_Event &e);
    virtual void onUpdate(TimeManager::Millisec);

protected:

    Cameras m_cameras;

private:

};

} // namespace engine
} // namespace nd

#endif /* !SCENE_HPP_ */
