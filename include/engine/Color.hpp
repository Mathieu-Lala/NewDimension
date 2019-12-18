/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Color
*/

#ifndef COLOR_HPP_
# define COLOR_HPP_

# include <cstdint>
# include <iostream>
# include <algorithm>

namespace nd {
namespace engine {

struct Color {

    using RGBA_component = float; // value normalized (0 to 1)
    using Hexa_value = unsigned int;

    constexpr Color() :
        r   (0.0f),
        g   (0.0f),
        b   (0.0f),
        a   (0.0f)
    { }

    constexpr Color(RGBA_component rr, RGBA_component gg, RGBA_component bb, RGBA_component aa = 1.0f) :
        r   (rr),
        g   (gg),
        b   (bb),
        a   (aa)
    { }

    RGBA_component r;
    RGBA_component g;
    RGBA_component b;
    RGBA_component a;

    constexpr Hexa_value asInteger() noexcept;

    constexpr inline Color normalize() const noexcept
    {
        return {
            std::max(0.0f, std::min(1.0f, this->r)),
            std::max(0.0f, std::min(1.0f, this->g)),
            std::max(0.0f, std::min(1.0f, this->b)),
            std::max(0.0f, std::min(1.0f, this->a)),
        };
    }

};

constexpr static Color White = { 1.0f, 1.0f, 1.0f, 1.0f };
constexpr static Color Black = { 0.0f, 0.0f, 0.0f, 1.0f };

} // namespace engine
} // namespace nd

constexpr inline nd::engine::Color operator*(const nd::engine::Color &color, float f) noexcept
{
    return {
        color.r * f,
        color.g * f,
        color.b * f,
        color.a * f,
    };
}

constexpr inline nd::engine::Color operator*=(nd::engine::Color &color, float f) noexcept
{
    color = color * f;
    return color;
}

constexpr inline nd::engine::Color operator+(const nd::engine::Color &color_1, const nd::engine::Color &color_2) noexcept
{
    return {
        color_1.r + color_2.r,
        color_1.g + color_2.g,
        color_1.b + color_2.b,
        color_1.a + color_2.a,
    };
}

constexpr inline nd::engine::Color::Hexa_value nd::engine::Color::asInteger() noexcept
{
    float max = std::max(a, std::max(r, std::max(g, b)));
    if (max > 1.0f)
        *this *= 1.0f / max;

    auto out = this->normalize();

    return
        (static_cast<int8_t>(out.a * 255) << 24) |
        (static_cast<int8_t>(out.r * 255) << 16) |
        (static_cast<int8_t>(out.g * 255) << 8) |
        static_cast<int8_t>(out.b * 255);
}

#endif /* !COLOR_HPP_ */
