/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** main
*/

#include "engine/Logger.hpp"
#include "config/config.hpp"
#include "engine/Window.hpp"
#include "engine/Scene.hpp"
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

    // just temp alias of type
    using V2u = nd::engine::math::Vector2u;
    using V3f = nd::engine::math::Vector3f;

    nd::engine::Core core;

    // normal window
    core.addWindow(std::make_unique<nd::engine::Window>(V2u { 300, 300 }, V2u { 300, 300 }));

    // bigger window, smaller resolution
    core.addWindow(std::make_unique<nd::engine::Window>(V2u { 700, 700 }, V2u { 200, 200 }));

    auto scene = core.setScene(std::make_unique<nd::engine::Scene>());
    scene->setCamera(std::make_unique<nd::engine::Camera>(V3f { 0.0f }, V3f { 0.0f, 0.0f, 1.0f }));

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
