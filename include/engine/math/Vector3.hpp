/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Vector3
*/

#ifndef VECTOR3_HPP_
# define VECTOR3_HPP_

# include "engine/math/function.hpp"

namespace nd {
namespace engine {
namespace math {

template<typename T>
struct Vector3 {

    T x;
    T y;
    T z;
    T w; // we use vector3 as quaternion

    constexpr inline Vector3(T value = T(0)) :
        x   (value),
        y   (value),
        z   (value),
        w   (T(1))
    { }

    constexpr inline Vector3(T xx, T yy, T zz, T ww = T(1)) :
        x   (xx),
        y   (yy),
        z   (zz),
        w   (ww)
    { }

    ~Vector3() = default;

    constexpr inline bool operator==(const Vector3 &other) const noexcept
    {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    constexpr inline bool operator!=(const Vector3 &other) const noexcept
    {
        return !(*this == other);
    }

    constexpr inline Vector3 operator+(const Vector3 &other) const noexcept
    {
        return {
            this->x + other.x,
            this->y + other.y,
            this->z + other.z
        };
    }

    constexpr inline Vector3 operator-(const Vector3 &other) const noexcept
    {
        return {
            this->x - other.x,
            this->y - other.y,
            this->z - other.z
        };
    }

    constexpr inline Vector3 &operator+=(const Vector3 &other) noexcept
    {
        *this = *this + other;
        return *this;
    }

    constexpr inline Vector3 &operator-=(const Vector3 &other) noexcept
    {
        *this = *this - other;
        return *this;
    }

    constexpr inline T length() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    constexpr inline Vector3 normalize() const noexcept
    {
        const auto len = length();
        const auto d = 1.0f / (len != T(0) ? len : T(1));
        return {
            x * d,
            y * d,
            z * d,
            w * d
        };
    }

    constexpr inline T dot(const Vector3 &other) const noexcept
    {
        return x * other.x + y * other.y + z * other.z;
    }

    constexpr inline Vector3 conjugate() const noexcept
    {
        return {
            - this->x,
            - this->y,
            - this->z,
            this->w
        };
    }

    constexpr inline Vector3 mult_coord(const Vector3 &other) const noexcept
    {
        return {
            this->x * other.x,
            this->y * other.y,
            this->z * other.z,
            this->w * other.w
        };
    }

    constexpr inline Vector3 operator*(const Vector3 &other) const noexcept
    {
        return {
            this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,
            this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,
            this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w,
            this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z
        };
    }

    constexpr inline Vector3 operator*(T m) const noexcept
    {
        return {
            this->x * m,
            this->y * m,
            this->z * m
        };
    }

    constexpr inline Vector3 getRightVector() const noexcept
    {
        return *this * Vector3(T(1), T(0), T(0)) * this->conjugate();
    }

    constexpr inline Vector3 getUpVector() const noexcept
    {
        return *this * Vector3(T(0), T(1), T(0)) * this->conjugate();
    }

    constexpr inline Vector3 getForwardVector() const noexcept
    {
        return *this * Vector3(T(0), T(0), T(1)) * this->conjugate();
    }

    constexpr inline Vector3 euler(float theta) const
    {
        theta = 0.5f * degree2rad(theta);

        return {
            this->x * std::sin(theta),
            this->y * std::sin(theta),
            this->z * std::sin(theta),
            std::cos(theta),
        };
    }

};

using Vector3f = Vector3<float>;

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !VECTOR3_HPP_ */
