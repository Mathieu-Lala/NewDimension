/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
# define RENDERER_HPP_

# include <utility>
# include "engine/Window.hpp"
# include "engine/math/Ray.hpp"
# include "engine/Material.hpp"
# include "engine/Color.hpp"

namespace nd {
namespace engine {

class Window;
class Scene;

class Renderer {
public:
    Renderer() = delete;

    static void render(Window *window, const Scene *scene);

protected:
private:

    static Color castRay(const math::Ray &, const Scene *, std::size_t depth = 1);


    static bool hasIntersection(const math::Ray &, const Scene *, math::Vector3f &hit_point, math::Vector3f &N, Material &);

    static std::tuple<float, float> getIllumination(const math::Ray &ray, const Scene *scene,
        const math::Vector3f &hit_point, const math::Vector3f &N, const Material &material);


    static constexpr math::Ray getReflectRay(const math::Vector3f &direction,
        const math::Vector3f &N, const math::Vector3f &hit_point) noexcept;

    static constexpr math::Ray getRefractRay(const math::Vector3f &direction,
        const math::Vector3f &N, const math::Vector3f &hit_point, float refractive_index, float eta_t = 1.0f) noexcept;


    static constexpr math::Vector3f reflect(const math::Vector3f &I, const math::Vector3f &N) noexcept;

};

} // namespace engine
} // namespace nd

#endif /* !RENDERER_HPP_ */
