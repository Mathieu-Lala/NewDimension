/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Renderer
*/

#include "engine/Renderer.hpp"
#include "engine/shapes/Sphere.hpp"
#include "engine/Window.hpp"
#include "engine/Camera.hpp"

void nd::engine::Renderer::render(nd::engine::Window *window)
{
    // todo : save the shape in a Scene class
    shape::Sphere s({ 0.0f, 0.0f, 100.0f}, 40.0f);

    Camera cam(math::Vector3f { 0.0f, 0.0f, 0.0f }, math::Vector3f { 0.0f, 0.0f, 1.0f });

    for (unsigned int y = 0; y != window->getResolution().y; y++)
        for (unsigned int x = 0; x != window->getResolution().x; x++) {

            auto x_norm = (x / float(window->getResolution().x)) * 2.0f - 1.0f * window->getAspectRatio();
            auto y_norm = (y / float(window->getResolution().y)) * 2.0f - 1.0f;

            math::Ray ray;
            cam.generateRay(x_norm, y_norm, ray);

            float t;
            if (s.intersect(ray, t) && t >= ray.m_t_min && t <= ray.m_t_max)
                // todo : get the color from the shape
                window->draw(x, y, 0xFF00FFFF);
        }
}
