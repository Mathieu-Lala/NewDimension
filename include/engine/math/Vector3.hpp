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
    T w; // we use vector3 as quaternion

    constexpr Vector3() :
        x   (T(0)),
        y   (T(0)),
        z   (T(0)),
        w   (T(1))
    { }

    constexpr Vector3(T value) :
        x   (value),
        y   (value),
        z   (value),
        w   (T(1))
    { }

    constexpr Vector3(T xx, T yy, T zz, T ww = T(1)) :
        x   (xx),
        y   (yy),
        z   (zz),
        w   (ww)
    { }

    ~Vector3() = default;

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

    constexpr inline T dot(const Vector3 &other) const noexcept
    {
        return x * other.x + y * other.y + z * other.z;
    }

    constexpr inline Vector3 conjugate() const noexcept
    {
        return Vector3 {
            -this->x,
            -this->y,
            -this->z,
            this->w
        };
    }

    constexpr inline Vector3 operator*(const Vector3 &other) const noexcept
    {
        return Vector3 {
            this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
            this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
            this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w,
            this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z
        };
    }
};

using Vector3f = Vector3<float>;

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !VECTOR3_HPP_ */
