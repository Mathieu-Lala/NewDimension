/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** main
*/

#include "engine/Logger.hpp"
#include "config/config.hpp"
#include "engine/Window.hpp"

int main(int, char **av) try
{
    NOTICE(
        "project name: " << PROJECT_NAME <<
        "version: " <<
        PROJECT_VERSION_MAJOR << "." <<
        PROJECT_VERSION_MINOR << "." <<
        PROJECT_VERSION_PATCH << " " <<
        "build type: " << PROJECT_BUILD_TYPE
    );

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw SDL_GetError();
    std::atexit([] { SDL_Quit(); });

    std::srand(std::time(nullptr));

    const nd::engine::math::Vector2u window_size = { 200, 200 };
    nd::engine::Window window(window_size, window_size);

    int frameDelta = 0;
    int counter = 0;
    auto color = std::rand() % 0xFFFFFFFF;

    while (window.isOpen()) {

        int t_start = SDL_GetTicks();

        auto resolution = window.getResolution();

        window.clear(0x00AAFF);

        if (counter >= 1000) {
            color = std::rand() % 0xFFFFFFFF;
            counter = 0;
        }
        for (auto j = 0u; j != resolution.y; j++)
            for (auto i = 0u; i != resolution.x; i++)
                if (i & j)
                    window.draw(i, j, color);

        window.display();


        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                window.setOpen(false);
                break;
            default:
                break;
            }
        }

        counter += frameDelta;

        frameDelta = SDL_GetTicks() - t_start;
    }

    return ND_SUCCESS;

}
catch (const std::exception &e) {

    CRITIC(av[0] << ": " << e.what());
    return ND_ERROR;

}
catch (...) {

    CRITIC(av[0] << ": Caught unexpected throw at main level");
    return ND_ERROR;

}
