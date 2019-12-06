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

    using ID = int;

    inline bool isOpen() const noexcept
        { return m_is_open; }

    using Pixel = unsigned int;

    void display();
    void clear(Pixel color);

    void draw(unsigned int x, unsigned int y, Pixel color);

    inline const math::Vector2u &getResolution() const noexcept
        { return m_screen_resolution; }

    void setResolution(const math::Vector2u &);

    void handleEvent(const SDL_Event &);

    unsigned int getSDL_ID() const noexcept
        { return SDL_GetWindowID(m_window); }

protected:
private:

    static ID s_current_id;
    const ID c_uid;

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
