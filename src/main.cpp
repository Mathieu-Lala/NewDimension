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
    INFO(
        "project name: " << PROJECT_NAME << " " <<
        "version: " <<
            PROJECT_VERSION_MAJOR << "." <<
            PROJECT_VERSION_MINOR << "." <<
            PROJECT_VERSION_PATCH << " " <<
        "build type: " << PROJECT_BUILD_TYPE
    );

    std::srand(std::time(nullptr));

    // just temp alias of type
    using V2u = nd::engine::math::Vector2u;
    using V3f = nd::engine::math::Vector3f;
    using Vp = nd::engine::math::Rect<unsigned int>;

    nd::engine::Core core;

    const V2u resolution = { 300, 300 };

    core.addWindow(std::make_unique<nd::engine::Window>(V2u { 500, 500 }, resolution));

    auto scene = core.setScene(std::make_unique<nd::engine::Scene>());

    scene->addCamera(std::make_unique<nd::engine::Camera>(
        V3f { 0.0f }, V3f { 0.0f, 0.0f, 1.0f }, Vp { 0, 0, 300, resolution.y / 2 }, 70.0f));
    scene->addCamera(std::make_unique<nd::engine::Camera>(
        V3f { 0.0f }, V3f { 0.0f, 0.0f, 1.0f }, Vp { 0, resolution.y / 2 , 300, resolution.y / 2 }, 100.0f));

    while (core.isRunning()) {

        core.run();

    }

    INFO(av[0] << ": End of program");
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
