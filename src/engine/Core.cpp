/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Core
*/

#include <algorithm>
#include "engine/Core.hpp"
#include "engine/Window.hpp"


// will change
class Renderer {
public:

    static void render(nd::engine::Window *w, int dt)
    {
        static auto color_1 = std::rand() % 0xFFFFFFFF;
        static auto color_2 = std::rand() % 0xFFFFFFFF;
        static int counter = 0;

        counter += dt;

        auto resolution = w->getResolution();
        w->clear((w->getSDL_ID() & 1) ? color_2 : color_1);
        if (counter >= 1000) {
            color_1 = std::rand() % 0xFFFFFFFF;
            color_2 = std::rand() % 0xFFFFFFFF;
            counter = 0;
        }
        for (auto j = 0u; j != resolution.y; j++)
            for (auto i = 0u; i != resolution.x; i++)
                if (i & j)
                    w->draw(i, j, (w->getSDL_ID() & 1) ? color_1 : color_2);
    }

private:
};


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
        Renderer::render(i.get(), /* tmp */ frameDelta / m_windows.size());
        i->display();
    }

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
    return std::any_of(m_windows.begin(), m_windows.end(), [](const auto &i) {
        return i && i->isOpen();
    });
}
