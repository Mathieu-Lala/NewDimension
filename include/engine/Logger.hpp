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
# include <ctime>
//# include <cstring>
# include <functional>

namespace nd {
namespace engine {

class Logger {
public:
    Logger() = delete;

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

        UNKNOWN,
    };

    inline static level get_current_level() noexcept
        { return s_current_level; }
    inline static void set_current_level(level new_level) noexcept
        { s_current_level = new_level; }

    struct data {
        level msg_level;
        const char *file;
        int line;
        const char *func;
        std::time_t timestamp;
    };

    static std::ostream &dump_info(const data &data_info);

    inline static void set_format(const std::string &new_format) noexcept
        { s_display_format = new_format; }

protected:
private:

    static std::ostream *s_stream;
    static level s_current_level;
    static std::string s_display_format;

    static constexpr std::ostream *DEFAULT_STREAM = &std::cerr;
    static constexpr level DEFAULT_LEVEL = DEBUG;
    static constexpr auto DEFAULT_DISPLAY_FORMAT =
        "[${info:level}] id:${info:uid} at:${style:underline}${info:timestamp}${style:reset} "
        "in file ${info:file} at line ${style:bold:underline}${info:line}${style:reset} "
        "in function ${style:fg-blue:bold}${info:func}${style:reset}:\r\n";

    using uid = std::size_t;
    static uid s_current_msg_uid;

    static constexpr std::array S_LEVEL_AS_STRING {
        std::make_pair(DEBUG,  "${style:fg-lightcyan}DEBUG${style:reset}"),
        std::make_pair(INFO,   "${style:fg-lightgreen}INFO${style:reset}"),
        std::make_pair(NOTICE, "${style:fg-green}NOTICE${style:reset}"),

        std::make_pair(WARNING, "${style:fg-lightyellow}WARNING${style:reset}"),
        std::make_pair(ERROR,   "${style:fg-red:bold}ERROR${style:reset}"),
        std::make_pair(ALERT,   "${style:fg-lightred:underline:bold}ALERT${style:reset}"),

        std::make_pair(CRITIC,    "${style:fg-black:blink:bg-yellow}CRITIC${style:reset}"),
        std::make_pair(EMERGENCY, "${style:fg-black:blink:bold:underline:bg-lightred}EMERGENCY${style:reset}"),
    };

    static constexpr std::optional<const char *> level_as_string(level search);

    using PairStyle = std::pair<const char *, const char *>;
    static constexpr std::array<const PairStyle, 47> S_SUPPORTED_STYLE {

        // Colors
        std::make_pair("fg-red", "31"),        std::make_pair("bg-red", "41"),
        std::make_pair("fg-lightred", "91"),   std::make_pair("bg-lightred", "101"),
        std::make_pair("fg-green", "32"),      std::make_pair("bg-green", "42"),
        std::make_pair("fg-lightgreen", "92"), std::make_pair("bg-lightgreen", "102"),
        std::make_pair("fg-blue", "34"),       std::make_pair("bg-blue", "44"),
        std::make_pair("fg-lightblue", "94"),  std::make_pair("bg-lightblue", "104"),

        std::make_pair("fg-yellow", "33"),       std::make_pair("bg-yellow", "43"),
        std::make_pair("fg-lightyellow", "93"),  std::make_pair("bg-lightyellow", "103"),
        std::make_pair("fg-magenta", "35"),      std::make_pair("bg-magenta", "45"),
        std::make_pair("fg-lightmagenta", "95"), std::make_pair("bg-lightmagenta", "105"),
        std::make_pair("fg-cyan", "36"),         std::make_pair("bg-cyan", "46"),
        std::make_pair("fg-lightcyan", "96"),    std::make_pair("bg-lightcyan", "106"),

        std::make_pair("fg-white", "97"),   std::make_pair("bg-white", "107"),
        std::make_pair("fg-lightgrey", "37"), std::make_pair("bg-lightgrey", "47"),
        std::make_pair("fg-darkgrey", "90"),  std::make_pair("bg-drakgrey", "100"),
        std::make_pair("fg-black", "30"),   std::make_pair("bg-black", "40"),

        std::make_pair("fg-default", "39"), std::make_pair("bg-default", "49"),

        // ... complete me

        // Styles / Effects
        std::make_pair("bold", "1"),      std::make_pair("bold-off", "21"),
        std::make_pair("dim", "2"),       std::make_pair("dim-off", "22"),
        std::make_pair("underline", "4"), std::make_pair("underline-off", "24"),

        std::make_pair("blink", "5"),     std::make_pair("blink-off", "25"),
        std::make_pair("inverse", "7"),   std::make_pair("inverse-off", "27"),
        std::make_pair("hidden", "8"),    std::make_pair("hidden-off", "28"),

        // ... complete me

        std::make_pair("reset", "0"),
    };

    static constexpr std::optional<PairStyle> get_style_value(const char *search);

};

} // namespace engine
} // namespace new dimension

# define LOG(level, exp) do {   \
    if (nd::engine::Logger::get_current_level() <= level)   \
        nd::engine::Logger::dump_info({ level, __FILE__, __LINE__, __func__, std::time(nullptr) }) \
            << exp << std::endl;   \
    } while (false)

# define DEBUG(exp)     LOG(nd::engine::Logger::DEBUG, exp)
# define INFO(exp)      LOG(nd::engine::Logger::INFO, exp)
# define NOTICE(exp)    LOG(nd::engine::Logger::NOTICE, exp)
# define WARNING(exp)   LOG(nd::engine::Logger::WARNING, exp)
# define ERROR(exp)     LOG(nd::engine::Logger::ERROR, exp)
# define ALERT(exp)     LOG(nd::engine::Logger::ALERT, exp)
# define CRITIC(exp)    LOG(nd::engine::Logger::CRITIC, exp)
# define EMERGENCY(exp) LOG(nd::engine::Logger::EMERGENCY, exp)

#endif /* !LOGGER_HPP_ */
