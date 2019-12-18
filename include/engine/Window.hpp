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
# include "engine/Color.hpp"

namespace nd {
namespace engine {

class Window {
public:
    Window(math::Vector2u window_size, math::Vector2u screen_resolution);
    ~Window();


    using ID = decltype(SDL_GetWindowID(nullptr));
    inline ID getID() const
        { return SDL_GetWindowID(m_window); }


    void display();
    void clear(Color::Hexa_value color);

    void draw(unsigned int x, unsigned int y, Color::Hexa_value color);


    inline const math::Vector2u &getResolution() const noexcept
        { return m_screen_resolution; }

    inline float getAspectRatio() const noexcept
        { return m_screen_resolution.x / static_cast<float>(m_screen_resolution.y); } // assuming X > Y

    void setResolution(const math::Vector2u &);


    void onEvent(const SDL_Event &e);


    inline std::size_t getRayTracingDepth() const noexcept
        { return m_ray_tracing_depth; }

protected:
private:

    math::Vector2u m_window_size;
    math::Vector2u m_screen_resolution;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Texture *m_texture;

    Color::Hexa_value *m_frame_buffer;

    bool m_is_open;

    std::size_t m_ray_tracing_depth;

};

} // namespace engine
} // namespace nd

#endif /* !WINDOW_HPP_ */
