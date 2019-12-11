/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Scene
*/

#include "engine/Scene.hpp"

nd::engine::Camera *nd::engine::Scene::addCamera(std::unique_ptr<Camera> &&cam) noexcept
{
    return m_cameras.emplace_front(std::move(cam)).get();
}

const std::list<std::unique_ptr<nd::engine::Camera>> &nd::engine::Scene::getCameras() const noexcept
{
    return m_cameras;
}

void nd::engine::Scene::onEvent(const SDL_Event &e)
{
    for (auto &i : this->m_cameras)
        i->onEvent(e);
}

void nd::engine::Scene::onUpdate(decltype(SDL_GetTicks()) dt)
{
    for (auto &i : this->m_cameras)
        i->onUpdate(dt);
}
