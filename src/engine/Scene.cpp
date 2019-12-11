/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Scene
*/

#include "engine/Scene.hpp"

void nd::engine::Scene::onEvent(const SDL_Event &e)
{
    if (this->m_camera)
        m_camera->onEvent(e);
}

void nd::engine::Scene::onUpdate(decltype(SDL_GetTicks()) dt)
{
    if (this->m_camera)
        m_camera->onUpdate(dt);
}
