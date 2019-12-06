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

class Core {
public:

    Core();
    ~Core() = default;

    Window *addWindow(std::unique_ptr<Window> &&w);

    void run();
    bool isRunning();

protected:
private:

    std::list<std::unique_ptr<Window>> m_windows;

    int frameDelta;

};

} // namespace engine
} // namespace nd

#endif /* !CORE_HPP_ */
