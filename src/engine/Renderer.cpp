/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Renderer
*/

#include "engine/Renderer.hpp"
#include "engine/shapes/Sphere.hpp"
#include "engine/Window.hpp"

void nd::engine::Renderer::render(nd::engine::Window *window)
{
    // todo : save the shape in a Scene class
    shape::Sphere s({ 200.0f, 200.0f, 50.0f}, 40.0f);

    for (math::Vector2u p = { 0, 0 }; p.y != window->getResolution().y; p.y++)
        for (p.x = 0; p.x != window->getResolution().x; p.x++) {
            // todo : normalise the position on the screen

            // todo : generate the ray from a Camera
            nd::engine::math::Ray ray;
            ray.m_origin = { float(p.x), float(p.y), 0.0f };
            ray.m_dest = { 0.0f, 0.0f, 1.0f };
            ray.m_t_min = 0.0001f;
            ray.m_t_max = 1000.0f;

            float t;
            if (s.intersect(ray, t)) {
                if (t >= ray.m_t_min && t <= ray.m_t_max)
                    // todo : get the color from the shape
                    window->draw(p.x, p.y, 0xFF00FFFF);
            }

        }
}
