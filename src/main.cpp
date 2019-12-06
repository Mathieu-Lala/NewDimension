/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** main
*/

#include "engine/Logger.hpp"
#include "config/config.hpp"
#include "engine/Window.hpp"
#include "engine/Core.hpp"

int main(int, char **av) try
{
    NOTICE(
        "project name: " << PROJECT_NAME << " " <<
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

    using V2u = nd::engine::math::Vector2u; // tmp

    nd::engine::Core core;
    core.addWindow(std::make_unique<nd::engine::Window>(V2u { 300, 300 }, V2u { 300, 300 }));
    core.addWindow(std::make_unique<nd::engine::Window>(V2u { 700, 700 }, V2u { 200, 200 }));

    while (core.isRunning()) {

        core.run();

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
