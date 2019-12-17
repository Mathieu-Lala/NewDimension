/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Scene
*/

#include <SDL2/SDL.h>
#include "engine/Scene.hpp"

nd::engine::Camera *nd::engine::Scene::addCamera(std::unique_ptr<Camera> &&cam) noexcept
{
    m_cameras.emplace_back(std::move(cam));
    return m_cameras.back().get();
}

const nd::engine::Scene::Cameras &nd::engine::Scene::getCameras() const noexcept
{
    return m_cameras;
}

void nd::engine::Scene::onEvent(const SDL_Event &e)
{
    for (auto &i : this->m_cameras)
        i->onEvent(e);
}

void nd::engine::Scene::onUpdate(TimeManager::Millisec dt)
{
    for (auto &i : this->m_cameras)
        i->onUpdate(dt);
}
