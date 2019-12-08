/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Core
*/

#include <algorithm>
#include "engine/Core.hpp"
#include "engine/Window.hpp"
#include "engine/Renderer.hpp"

nd::engine::Core::Core() :
    frameDelta  (0)
{ }

nd::engine::Window *nd::engine::Core::addWindow(std::unique_ptr<Window> &&w)
{
    return m_windows.emplace_front(std::move(w)).get();
}

void nd::engine::Core::run()
{
    int t_start = SDL_GetTicks();

    for (auto &i : m_windows) {
        Renderer::render(i.get());
        i->display();
    }

    // tmp
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
            m_windows.remove_if([&e](const auto &i) {
                return i->getSDL_ID() == e.window.windowID;
            });
        }
    }

    frameDelta = SDL_GetTicks() - t_start;
}

bool nd::engine::Core::isRunning()
{
    return !!m_windows.size();
}
