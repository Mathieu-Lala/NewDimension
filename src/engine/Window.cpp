/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Window
*/

#include <exception>
#include <stdexcept>
#include <cstring>
#include "engine/Window.hpp"
#include "engine/Logger.hpp"

nd::engine::Window::Window(math::Vector2u window_size, math::Vector2u screen_resolution) :
    m_window_size       (std::move(window_size)),
    m_screen_resolution (std::move(screen_resolution)),

    m_window            (nullptr),
    m_renderer          (nullptr),
    m_texture           (nullptr),
    m_frame_buffer      (nullptr)
{
    m_window = SDL_CreateWindow(
        "", // should be configurable
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_window_size.x,
        m_window_size.y,
        SDL_WINDOW_SHOWN); // should be configurable
    if (!m_window)
        throw std::runtime_error(SDL_GetError());

    m_renderer = SDL_CreateRenderer(
        m_window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC // should be configurable
    );
    if (!m_renderer)
        throw std::runtime_error(SDL_GetError());

    NOTICE("Window:: Created new window [" << getID() << "]");

    setResolution(m_screen_resolution);
}

nd::engine::Window::~Window()
{
    NOTICE("Window:: Destruction of window [" << getID() << "]");

    if (m_texture)
        SDL_DestroyTexture(m_texture);

    if (m_frame_buffer)
        delete[] m_frame_buffer;

    if (m_renderer)
        SDL_DestroyRenderer(m_renderer);

    if (m_window)
        SDL_DestroyWindow(m_window);
}

void nd::engine::Window::display()
{
    if (SDL_UpdateTexture(m_texture, nullptr, m_frame_buffer, m_screen_resolution.x * sizeof(Pixel)) == -1)
        throw std::runtime_error(SDL_GetError());

    if (SDL_RenderClear(m_renderer) == -1)
        throw std::runtime_error(SDL_GetError());

    if (SDL_RenderCopy(m_renderer, m_texture, nullptr, nullptr) == -1)
        throw std::runtime_error(SDL_GetError());

    SDL_RenderPresent(m_renderer);
}

void nd::engine::Window::clear(Pixel color)
{
    std::fill_n(m_frame_buffer, m_screen_resolution.x * m_screen_resolution.y, color);
}

void nd::engine::Window::draw(unsigned int x, unsigned int y, Pixel color)
{
    m_frame_buffer[x + y * m_screen_resolution.x] = color;
}

void nd::engine::Window::setResolution(const math::Vector2u &new_resolution)
{
    if (!new_resolution.x || !new_resolution.y) {
        WARNING("Window:: Can not set the resolution of (" <<
            new_resolution.x << ", " << new_resolution.y << ") to window [" << getID() << "]");
        return;
    }

    m_screen_resolution = new_resolution;

    if (m_texture)
        SDL_DestroyTexture(m_texture);

    if (m_frame_buffer)
        delete[] m_frame_buffer;

    m_texture = SDL_CreateTexture(
        m_renderer,
        SDL_PIXELFORMAT_ARGB8888, // should be configurable
        SDL_TEXTUREACCESS_TARGET,
        m_screen_resolution.x,
        m_screen_resolution.y
    );
    if (!m_texture)
        throw std::runtime_error(SDL_GetError());

    m_frame_buffer = new Pixel[m_screen_resolution.x * m_screen_resolution.y];
    if (!m_frame_buffer)
        throw std::bad_alloc();

//#define DEBUG_RESOLUTION
#ifdef DEBUG_RESOLUTION
    NOTICE("Window:: Set resolution of window [" << getID() << "](" <<
        m_screen_resolution.x << ", " << m_screen_resolution.y << ")");
#endif
}

void nd::engine::Window::onEvent(const SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.window.windowID == getID()) {

        if (e.key.keysym.scancode == SDL_SCANCODE_KP_PLUS)
            setResolution(getResolution() + math::Vector2u { 10, 10 });
        else if (e.key.keysym.scancode == SDL_SCANCODE_KP_MINUS)
            setResolution(getResolution() - math::Vector2u { 10, 10 });

    }
}
