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
# include "engine/shapes/Sphere.hpp"
# include "engine/LightingPoint.hpp"

namespace nd {
namespace engine {

class Sphere;

class Scene {
public:
    Scene() = default;
    ~Scene() = default;

    using Cameras = std::vector<std::unique_ptr<Camera>>;

    nd::engine::Camera *addCamera(std::unique_ptr<Camera> &&cam) noexcept;

    const Cameras &getCameras() const noexcept;

    virtual void onEvent(const SDL_Event &e);
    virtual void onUpdate(TimeManager::Millisec);

    const std::vector<shape::Sphere> &getSpheres() const noexcept
        { return m_spheres; }

    const std::vector<LightingPoint> &getLights() const noexcept
        { return m_lightingPoints; }

    const Color &getSkyColor() const noexcept
        { return m_sky_color; }

    void setSkyColor(const Color &color) noexcept
        { m_sky_color = color; }

protected:

    Cameras m_cameras;

    std::vector<shape::Sphere> m_spheres;

    std::vector<LightingPoint> m_lightingPoints;

    Color m_sky_color;

private:

};

} // namespace engine
} // namespace nd

#endif /* !SCENE_HPP_ */
