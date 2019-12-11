/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Core
*/

#include <algorithm>
#include "engine/Core.hpp"
#include "engine/Window.hpp"
#include "engine/Scene.hpp"
#include "engine/Renderer.hpp"

nd::engine::Core::Core() :
    frameDelta  (0)
{ }

nd::engine::Window *nd::engine::Core::addWindow(std::unique_ptr<Window> &&w)
{
    return m_windows.emplace_front(std::move(w)).get();
}

nd::engine::Scene *nd::engine::Core::setScene(std::unique_ptr<Scene> &&scene)
{
    m_scene = std::move(scene);
    return m_scene.get();
}

void nd::engine::Core::run()
{
    Millisec t_start = SDL_GetTicks();

    for (auto &i : m_windows) {
        i->clear(0x00);
        Renderer::render(i.get(), m_scene.get());
        i->display();
    }

    // tmp
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
            m_windows.remove_if([&e](const auto &i) { return i->getID() == e.window.windowID; });

        } else {

            for (auto &i : m_windows)
                i->onEvent(e);

            if (m_scene)
                m_scene->onEvent(e);
        }
    }

    if (m_scene)
        m_scene->onUpdate(frameDelta);

    frameDelta = SDL_GetTicks() - t_start;
}

bool nd::engine::Core::isRunning()
{
    return !!m_windows.size();
}
