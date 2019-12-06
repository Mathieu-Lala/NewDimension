/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
# define SPHERE_HPP_

# include <utility>
# include <cmath>
# include "engine/math/Vector3.hpp"
# include "engine/math/Ray.hpp"
# include "engine/math/function.hpp"

namespace nd {
namespace engine {
namespace shape {

class Sphere {
public:
    Sphere() = default;
    Sphere(const math::Vector3f &pos, float radius) :
        m_pos       (std::move(pos)),
        m_radius    (radius)
    { }

    ~Sphere() = default;

    constexpr bool intersect(const math::Ray &ray, float &t)
    {
        const auto oc = ray.m_origin - this->m_pos;

        const auto a = ray.m_dest.dot(ray.m_dest);
        const auto b = 2 * oc.dot(ray.m_dest);
        const auto c = oc.dot(oc) - std::pow(this->m_radius, 2);

        float t0 = 0;
        float t1 = 0;
        if (!math::solveQuadratic(a, b, c, t0, t1))
            return false;

        if (t0 < 0) {
            if (t1 < 0)
                return false;
            t0 = t1;
        }

        t = t0;

        return true;
    }

protected:
private:

    math::Vector3f m_pos;
    float m_radius;

};

} // namespace shape
} // namespace engine
} // namespace nd

#endif /* !SPHERE_HPP_ */
