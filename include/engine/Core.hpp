/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Core
*/

#ifndef CORE_HPP_
# define CORE_HPP_

# include <list>
# include <memory>

namespace nd {
namespace engine {

class Window;
class Scene;
class TimeManager;

class Core {
public:

    Core();
    ~Core();

    Window *addWindow(std::unique_ptr<Window> &&);
    Scene *setScene(std::unique_ptr<Scene> &&);

    void run();

protected:
private:

    void renderWindow(const std::unique_ptr<Window> &);
    void handleWindowEvent(const std::unique_ptr<Window> &, const SDL_WindowEvent &);

    std::list<std::unique_ptr<Window>> m_windows;
    std::unique_ptr<Scene> m_scene;

    TimeManager m_time_manager;

};

} // namespace engine
} // namespace nd

#endif /* !CORE_HPP_ */
