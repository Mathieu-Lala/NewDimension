/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Core
*/

#include <algorithm>
#include <chrono>
#include <SDL2/SDL.h>

#include "engine/Window.hpp"
#include "engine/Scene.hpp"
#include "engine/Renderer.hpp"
#include "engine/TimeManager.hpp"
#include "engine/Core.hpp"

#include "engine/Logger.hpp"

nd::engine::Core::Core()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());
}

nd::engine::Core::~Core()
{
    SDL_Quit();
}

nd::engine::Window *nd::engine::Core::addWindow(std::unique_ptr<Window> &&w)
{
    return m_windows.emplace_front(std::move(w)).get();
}

nd::engine::Scene *nd::engine::Core::setScene(std::unique_ptr<Scene> &&scene)
{
    m_scene = std::move(scene);
    return m_scene.get();
}

void nd::engine::Core::renderWindow(const std::unique_ptr<Window> &w)
{
    w->clear(0x00);
    Renderer::render(w.get(), m_scene.get());
    w->display();
}

void nd::engine::Core::handleWindowEvent(const std::unique_ptr<Window> &w, const SDL_WindowEvent &e)
{
    switch (e.event) {
    case SDL_WINDOWEVENT_CLOSE:
        m_windows.remove(w);
        break;
    default:
        break;
    }
}

void nd::engine::Core::run()
{
    m_time_manager.init();

    while (!!m_windows.size()) {

        auto elapsedTime = m_time_manager.getElapsedTime();

        for (auto &i : m_windows)
            this->renderWindow(i);

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_WINDOWEVENT:

                handleWindowEvent(*std::find_if(m_windows.begin(), m_windows.end(),
                    [&e](const auto &i) { return i->getID() == e.window.windowID; }), e.window);
                break;

            case SDL_KEYDOWN:
            case SDL_KEYUP:

                if (e.key.keysym.scancode == SDL_SCANCODE_F1) {
                    NOTICE("Elapsed time: " << elapsedTime);
                    break;
                }

                for (auto &i : m_windows)
                    i->onEvent(e);
                if (m_scene)
                    m_scene->onEvent(e);

                break;

            default:
                break;
            }
        }

        if (m_scene)
            m_scene->onUpdate(elapsedTime);
    }
}
