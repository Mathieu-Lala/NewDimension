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

void nd::engine::Renderer::render(Window *window, const Scene *scene)
{
    // todo : save the shape in a Scene class
    shape::Sphere s({ 0.0f, 0.0f, 100.0f}, 40.0f);

    for (auto &i : scene->getCameras()) {

        auto &viewport = i->getViewPort();

        for (unsigned int y = viewport.top; y != viewport.top + viewport.height; y++)
            for (unsigned int x = viewport.left; x != viewport.left + viewport.width; x++) {

                auto x_norm = ((x - viewport.left) /
                    static_cast<float>(viewport.width)) * 2.0f - 1.0f * window->getAspectRatio();
                auto y_norm = ((y - viewport.top) /
                    static_cast<float>(viewport.height)) * 2.0f - 1.0f;

                auto ray = i->generateRay(x_norm, y_norm);

                float t;
                if (s.intersect(ray, t) && t >= ray.m_t_min && t <= ray.m_t_max)
                    window->draw(x, y, 0xFF00FFFF);

            }
    }
}
