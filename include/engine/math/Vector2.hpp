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

};

using Vector2u = Vector2<unsigned int>;

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !VECTOR2_HPP_ */
