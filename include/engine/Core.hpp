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
# include <SDL2/SDL.h>

namespace nd {
namespace engine {

class Window;
class Scene;

class Core {
public:

    Core();
    ~Core() = default;

    Window *addWindow(std::unique_ptr<Window> &&);
    Scene *setScene(std::unique_ptr<Scene> &&);

    void run();
    bool isRunning();

    using Millisec = decltype(SDL_GetTicks());

protected:
private:

    std::list<std::unique_ptr<Window>> m_windows;

    std::unique_ptr<Scene> m_scene;

    // todo : move that somewhere else
    Millisec frameDelta;

};

} // namespace engine
} // namespace nd

#endif /* !CORE_HPP_ */
