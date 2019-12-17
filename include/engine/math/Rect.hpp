/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Rect
*/

#ifndef RECT_HPP_
# define RECT_HPP_

namespace nd {
namespace engine {
namespace math {

template<typename T>
struct Rect {

    T left;
    T top;
    T width;
    T height;

    constexpr Rect(T value = T(0)) :
        left    (value),
        top     (value),
        width   (value),
        height  (value)
    { }

    constexpr Rect(T ll, T tt, T ww, T hh) :
        left    (ll),
        top     (tt),
        width   (ww),
        height  (hh)
    { }

    inline constexpr bool contain(T x, T y) const noexcept
    {
        return this->left <= x && x <= this->left + this->width &&
            this->top <= y && y <= this->top + this->height;
    }

    constexpr inline Rect operator*(const Rect &other) const
    {
        return {
            this->left * other.left,
            this->top * other.top,
            this->width * other.width,
            this->height * other.height,
        };
    }

};

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !RECT_HPP_ */
