/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
# define VECTOR2_HPP_

namespace nd {
namespace engine {
namespace math {

template<typename T>
struct Vector2 {

    T x;
    T y;

    constexpr Vector2(T value = T(0)) :
        x   (value),
        y   (value)
    { }

    constexpr Vector2(T xx, T yy) :
        x   (xx),
        y   (yy)
    { }

    constexpr inline Vector2 operator+(const Vector2 &other) const noexcept
    {
        return {
            this->x + other.x,
            this->y + other.y
        };
    }

    constexpr inline Vector2 operator-(const Vector2 &other) const noexcept
    {
        return {
            this->x - other.x,
            this->y - other.y
        };
    }


};

using Vector2u = Vector2<unsigned int>;

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !VECTOR2_HPP_ */
