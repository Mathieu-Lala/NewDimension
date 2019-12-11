/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Window
*/

#ifndef WINDOW_HPP_
# define WINDOW_HPP_

# include <SDL2/SDL.h>
# include "engine/math/Vector2.hpp"

namespace nd {
namespace engine {

class Window {
public:
    Window(math::Vector2u window_size, math::Vector2u screen_resolution);
    ~Window();


    using ID = decltype(SDL_GetWindowID(nullptr));
    inline ID getID() const
        { return SDL_GetWindowID(m_window); }


    using Pixel = unsigned int;

    void display();
    void clear(Pixel color);

    void draw(unsigned int x, unsigned int y, Pixel color);


    inline const math::Vector2u &getResolution() const noexcept
        { return m_screen_resolution; }

    inline float getAspectRatio() const noexcept
        { return m_screen_resolution.x / static_cast<float>(m_screen_resolution.y); } // assuming X > Y

    void setResolution(const math::Vector2u &);


    void onEvent(const SDL_Event &e);

protected:
private:

    math::Vector2u m_window_size;
    math::Vector2u m_screen_resolution;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;

    Pixel *m_frame_buffer;

    bool m_is_open;

};

} // namespace engine
} // namespace nd

#endif /* !WINDOW_HPP_ */
