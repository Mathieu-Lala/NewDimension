/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Renderer
*/

#include <algorithm>
#include "engine/Renderer.hpp"
#include "engine/shapes/Sphere.hpp"
#include "engine/Window.hpp"
#include "engine/Scene.hpp"

constexpr nd::engine::math::Vector3f nd::engine::Renderer::reflect(const math::Vector3f &I, const math::Vector3f &N) noexcept
{
    return I - N * 2.0f * I.dot(N);
}

constexpr nd::engine::math::Ray nd::engine::Renderer::getReflectRay(
    const math::Vector3f &direction, const math::Vector3f &N, const math::Vector3f &hit_point) noexcept
{
    const auto reflect_direction = reflect(direction, N).normalize();
    return {
        hit_point + N * (reflect_direction.dot(N) < 0.0f ? - 1e-3 : 1e-3),
        reflect_direction,
    };
}

constexpr nd::engine::math::Ray nd::engine::Renderer::getRefractRay(const math::Vector3f &direction,
    const math::Vector3f &N, const math::Vector3f &hit_point, float refractive_index, float eta_t) noexcept
{
    const auto cosi = - std::max(-1.0f, std::min(1.0f, direction.dot(N)));
    if (cosi < 0.0f)
        return getRefractRay(direction, N.conjugate(), refractive_index, eta_t);

    const auto eta = refractive_index / (eta_t ? eta_t : 1.0f);
    const auto k = 1.0f - std::pow(eta, 2) * (1.0f - std::pow(cosi, 2));

    const auto refract_direction = k < 0.0f ?
        math::Vector3f(1.0f, 0.0f, 0.0f) :
        (direction * eta + N * (eta * cosi - std::sqrt(k))).normalize();

    return {
        hit_point + N * (refract_direction.dot(N) < 0.0f ? - 1e-3 : 1e-3),
        refract_direction
    };
}

bool nd::engine::Renderer::hasIntersection(
    const math::Ray &ray, const Scene *scene,
    math::Vector3f &hit_point, math::Vector3f &N, Material &material)
{
    auto minimun_dist = std::numeric_limits<float>::max();

    for (auto &shape : scene->getSpheres()) {

        float dist;
        if (shape.intersect(ray, dist) && dist >= ray.m_t_min && dist <= ray.m_t_max && dist < minimun_dist) {
            minimun_dist = dist;
            hit_point = ray.m_origin + ray.m_dest * dist;
            N = (hit_point - shape.getCenter()).normalize();
            material = shape.getMaterial();
        }

    }

    return minimun_dist < ray.m_t_max;
}

std::tuple<float, float> nd::engine::Renderer::getIllumination(const math::Ray &ray, const Scene *scene,
    const math::Vector3f &hit_point, const math::Vector3f &N, const Material &material)
{
    float diffuse_light_intensity = 0.0f;
    float specular_light_intensity = 0.0f;

    const auto get_light_ray = [](const LightingPoint &light, const math::Vector3f &hit_point, const math::Vector3f &N) {

        const auto light_dir = (light.m_position - hit_point).normalize();
        return math::Ray(hit_point + N * (light_dir.dot(N) < 0.0f ? - 1e-3 : 1e-3), light_dir);

    };

    for (auto &i : scene->getLights()) {

        const auto ray_light = get_light_ray(i, hit_point, N);

        math::Vector3f shadow_point;
        math::Vector3f shadow_N;
        Material tmpmaterial;

        if (hasIntersection(ray_light, scene, shadow_point, shadow_N, tmpmaterial)
            && (shadow_point - ray_light.m_origin).length() < (i.m_position - hit_point).length())
            continue;

        diffuse_light_intensity += i.m_intensity * std::max(0.0f, ray_light.m_dest.dot(N));

        const auto reflect_ligth = reflect(ray_light.m_dest.conjugate(), N).conjugate();
        specular_light_intensity += std::pow(std::max(0.0f, reflect_ligth.dot(ray.m_dest)), material.m_specular_exponent) * i.m_intensity;
    }

    return std::make_tuple(diffuse_light_intensity, specular_light_intensity);
}

nd::engine::Color nd::engine::Renderer::castRay(const math::Ray &ray, const Scene *scene, std::size_t depth)
{
    math::Vector3f hit_point;
    math::Vector3f N;
    Material material;

    if (depth == 0ul || !hasIntersection(ray, scene, hit_point, N, material))
        return scene->getSkyColor();

    const auto reflected_ray = getReflectRay(ray.m_dest, N, hit_point);
    const auto refracted_ray = getRefractRay(ray.m_dest, N, hit_point, material.m_refractive_index);

    const auto reflect_color = castRay(reflected_ray, scene, depth - 1ul);
    const auto refract_color = castRay(refracted_ray, scene, depth - 1ul);

    const auto [diffuse_light_intensity, specular_light_intensity] =
        getIllumination(ray, scene, hit_point, N, material);

    return
        material.m_diffuse_color * diffuse_light_intensity * material.m_albedo[0] +
        White * specular_light_intensity * material.m_albedo[1] +
        reflect_color * material.m_albedo[2] +
        refract_color * material.m_albedo[3];
}

void nd::engine::Renderer::render(Window *window, const Scene *scene)
{
    const auto &res = window->getResolution();

    for (auto &cam : scene->getCameras()) {

        const auto viewport = cam->getViewPort() * math::Rect {
            static_cast<float>(res.x), static_cast<float>(res.y),
            static_cast<float>(res.x), static_cast<float>(res.y)
        };

        for (auto y = viewport.top; y < viewport.top + viewport.height; y++)
            for (auto x = viewport.left; x < viewport.left + viewport.width; x++) {

                const auto x_norm = ((x - viewport.left) / viewport.width) * 2.0f - 1.0f * window->getAspectRatio();
                const auto y_norm = ((y - viewport.top) / viewport.height) * 2.0f - 1.0f;

                const auto ray = cam->generateRay(x_norm, y_norm);

                window->draw(x, y, castRay(ray, scene, window->getRayTracingDepth()).asInteger());

            }
    }
}
