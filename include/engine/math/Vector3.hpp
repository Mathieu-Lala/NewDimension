/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Vector3
*/

#ifndef VECTOR3_HPP_
# define VECTOR3_HPP_

namespace nd {
namespace engine {
namespace math {

template<typename T>
struct Vector3 {

    T x;
    T y;
    T z;

    constexpr inline Vector3 operator+(const Vector3 &other) const noexcept
    {
        return Vector3 {
            this->x + other.x,
            this->y + other.y,
            this->z + other.z
        };
    }

    constexpr inline Vector3 operator-(const Vector3 &other) const noexcept
    {
        return Vector3 {
            this->x - other.x,
            this->y - other.y,
            this->z - other.z
        };
    }

    constexpr inline T dot(const Vector3 &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

};

using Vector3f = Vector3<float>;

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !VECTOR3_HPP_ */
