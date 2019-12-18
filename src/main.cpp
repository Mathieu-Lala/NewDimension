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

class TestScene : public nd::engine::Scene {
public:
    TestScene()
    {
        using namespace nd::engine;
        using Vp = Camera::ViewPort;
        using V3f = math::Vector3f;

        this->addCamera(std::unique_ptr<Camera>(new Camera(
            V3f { 0.0f }, V3f { 0.0f, 0.0f, 1.0f }, Vp { 0.0f, 0.0f, 1.0f, 1.0f }, 70.0f)));

        this->m_lightingPoints.push_back(LightingPoint({ -20.0f, 20.0f,  20.0f }, 1.5f));
        this->m_lightingPoints.push_back(LightingPoint({  30.0f, 50.0f, -25.0f }, 1.8f));
        this->m_lightingPoints.push_back(LightingPoint({  30.0f, 20.0f,  30.0f }, 1.7f));

        Material ivory      (1.0f, std::array { 0.6f,  0.3f, 0.1f, 0.0f }, Color (0.4, 0.4, 0.3),   50.0f);
        Material glass      (1.5f, std::array { 0.0f,  0.5f, 0.1f, 0.8f }, Color (0.6, 0.7, 0.8),  125.0f);
        Material red_rubber (1.0f, std::array { 0.9f,  0.1f, 0.0f, 0.0f }, Color (0.3, 0.1, 0.1),   10.0f);
        Material mirror     (1.0f, std::array { 0.0f, 10.0f, 0.8f, 0.0f }, Color (1.0, 1.0, 1.0), 1425.0f);

        this->m_spheres.push_back(shape::Sphere({ -3.0f,  0.0f, -16.0f }, 2.0f,      ivory));
        this->m_spheres.push_back(shape::Sphere({ -1.0f, -1.5f, -12.0f }, 2.0f,      glass));
        this->m_spheres.push_back(shape::Sphere({  1.5f, -0.5f, -18.0f }, 3.0f, red_rubber));
        this->m_spheres.push_back(shape::Sphere({  7.0f,  5.0f, -18.0f }, 4.0f,     mirror));

        this->setSkyColor(Color(0.05f, 0.05f, 0.08f, 0.5f));
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
    core.addWindow(std::make_unique<nd::engine::Window>(
        nd::engine::math::Vector2u { 700, 700 },
        nd::engine::math::Vector2u { 300, 300 })
    );

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
