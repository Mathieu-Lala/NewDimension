/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Vector2
*/

#ifndef VECTOR2_HPP_
# define VECTOR2_HPP_

# include <cctype>

namespace nd {
namespace engine {
namespace math {

template<typename T>
struct Vector2 {

    T x;
    T y;

};

//using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;
//using Vector2ul = Vector2<std::size_t>;

} // namespace math
} // namespace engine
} // namespace nd

#endif /* !VECTOR2_HPP_ */
