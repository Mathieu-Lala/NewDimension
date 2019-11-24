/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
# define LOGGER_HPP_

# include <ostream>
# include <iostream>
# include <array>

namespace engine {

class Logger {
public:
    Logger() = delete;

    static std::ostream &get_stream();
    static bool set_stream(const std::string_view filepath);

    enum level {
        DEBUG,
        INFO,
        NOTICE,

        WARNING,
        ERROR,
        ALERT,

        CRITIC,
        EMERGENCY,
    };

    static level get_current_level() noexcept;
    static void set_current_level(level new_level) noexcept;

    static std::ostream &dump_info(level msg_leve, const char *file, int line, const char *func);

    static void set_format(const std::string &) noexcept;

protected:
private:

    static std::ostream *s_stream;
    static constexpr std::ostream *DEFAULT_STREAM = &std::cerr;

    static level s_current_level;
    static constexpr level DEFAULT_LEVEL = DEBUG;

    static constexpr std::array S_LEVEL_AS_STRING = {
        std::make_pair(DEBUG,  "DEBUG"),
        std::make_pair(INFO,   "INFO"),
        std::make_pair(NOTICE, "NOTICE"),

        std::make_pair(WARNING, "WARNING"),
        std::make_pair(ERROR,   "ERROR"),
        std::make_pair(ALERT,   "ALERT"),

        std::make_pair(CRITIC,    "CRITIC"),
        std::make_pair(EMERGENCY, "EMERGENCY"),
    };

    using uid = std::size_t;

    static uid s_current_msg_uid;

    static std::string s_display_format;

};

} // namespace nd

#define LOG(level, exp) {   \
    if (engine::Logger::get_current_level() >= level)   \
        engine::Logger::dump_info(level, __FILE__, __LINE__, __func__) << exp << std::endl;   \
    }

#endif /* !LOGGER_HPP_ */
