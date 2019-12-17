/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** TimeManager
*/

#ifndef TIMEMANAGER_HPP_
# define TIMEMANAGER_HPP_

# include <chrono>

namespace nd {
namespace engine {

class TimeManager {
public:
    TimeManager() = default;
    ~TimeManager() = default;

    using Millisec = std::chrono::milliseconds::rep;

    inline void init()
    {
        m_last_call = std::chrono::system_clock::now();
    }

    inline Millisec getElapsedTime()
    {
        const auto last = m_last_call;
        const auto now = std::chrono::system_clock::now();

        m_last_call = now;

        return std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
    }

protected:
private:

    std::chrono::system_clock::time_point m_last_call;

};

} // namespace engine
} // namespace nd

#endif /* !TIMEMANAGER_HPP_ */
