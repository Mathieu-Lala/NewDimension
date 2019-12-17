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
#include "engine/TimeManager.hpp"
#include "engine/Core.hpp"

// just temp alias of type
using V2u = nd::engine::math::Vector2u;
using V3f = nd::engine::math::Vector3f;
using Vp = nd::engine::Camera::ViewPort;

class TestScene : public nd::engine::Scene {
public:
    TestScene()
    {
        this->addCamera(std::unique_ptr<nd::engine::Camera>(new nd::engine::Camera(
            V3f { 0.0f }, V3f { 0.0f, 0.0f, 1.0f }, Vp { 0.0f, 0.0f, 1.0f, 0.5f }, 70.0f)));

        this->addCamera(std::unique_ptr<nd::engine::Camera>(new nd::engine::Camera(
            V3f { 0.0f }, V3f { 0.0f, 0.0f, 1.0f }, Vp { 0.0f, 0.5f, 1.0f, 0.5f }, 90.0f)));
    }

    ~TestScene() = default;

private:

};

int main(int, char **av) try
{
    INFO(
        "project name: " << PROJECT_NAME << " " <<
        "version: " <<
            PROJECT_VERSION_MAJOR << "." <<
            PROJECT_VERSION_MINOR << "." <<
            PROJECT_VERSION_PATCH << " " <<
        "build type: " << (PROJECT_BUILD_TYPE == Debug ? "Debug" : "Release")
    );

    std::srand(std::time(nullptr));

    nd::engine::Core core;
    core.addWindow(std::make_unique<nd::engine::Window>(V2u { 500, 500 }, V2u { 300, 300 }));

    core.setScene(std::unique_ptr<nd::engine::Scene>(new TestScene));

    core.run();

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
