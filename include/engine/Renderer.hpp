/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Renderer
*/

#ifndef RENDERER_HPP_
# define RENDERER_HPP_

namespace nd {
namespace engine {

class Window;

class Renderer {
public:
    Renderer() = delete;

    static void render(Window *window);

protected:
private:
};

} // namespace engine
} // namespace nd

#endif /* !RENDERER_HPP_ */
