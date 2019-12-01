/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Logger
*/

#include <fstream>
#include <cstring>
#include "engine/Logger.hpp"

std::ostream *nd::engine::Logger::s_stream = nd::engine::Logger::DEFAULT_STREAM;
nd::engine::Logger::level nd::engine::Logger::s_current_level = nd::engine::Logger::DEFAULT_LEVEL;
nd::engine::Logger::uid nd::engine::Logger::s_current_msg_uid = 0ul;
std::string nd::engine::Logger::s_display_format = nd::engine::Logger::DEFAULT_DISPLAY_FORMAT;

bool nd::engine::Logger::set_stream(const std::string_view filepath)
{
    static std::ofstream f;
    if (f.is_open())
        f.close();

    f.open(filepath.data());
    if (!f.is_open())
        return false;

    s_stream = &f;
    return true;
}

std::ostream &nd::engine::Logger::dump_info(const data &data_info)
{
    if (!s_stream)
        throw std::runtime_error("engine::Logger #no stream set#");

    // function printing some characters and returning the new position to print
    using Displayer = std::function<std::size_t(const std::string_view)>;

    Displayer flags_checker;

    // loop through a string and check for special flag
    const auto print_string = [&flags_checker](const std::string_view str) {
        for (std::size_t i = 0ul; i < str.size();)
            i += flags_checker(str.data() + i);
    };

    flags_checker = [&flags_checker, &data_info, &print_string](const std::string_view search) {

        // styles flags
        Displayer style_parser;
        style_parser = [&style_parser](const std::string_view str) {
            const auto style_value = get_style_value(str.data()).value_or(PairStyle { "", "" });
            *s_stream << "\e[" << style_value.second << "m";

            const auto len = std::strlen(style_value.first);
            return len + 1ul + (*(str.data() + len) != ':' ? 0ul :
                style_parser(str.data() + len + 1ul));
        };

        using PairFlag = std::pair<const char *, const Displayer>;

        // information flags
        const std::array<const PairFlag, 7> INFO_FLAG {
            PairFlag { "uid}",       [&data_info](const std::string_view) { *s_stream << s_current_msg_uid++; return 0ul; } },
            PairFlag { "timestamp}", [&data_info](const std::string_view) { *s_stream << data_info.timestamp; return 0ul; } },
            PairFlag { "file}",      [&data_info](const std::string_view) { *s_stream << data_info.file; return 0ul; } },
            PairFlag { "line}",      [&data_info](const std::string_view) { *s_stream << data_info.line; return 0ul; } },
            PairFlag { "func}",      [&data_info](const std::string_view) { *s_stream << data_info.func; return 0ul; } },
            PairFlag { "level}",     [&data_info, &print_string](const std::string_view) {
                return print_string(level_as_string(data_info.msg_level).value_or("")), 0ul;
            } },
        };

        // flags checker
        const auto check_flags = [](const std::string_view str, const auto &array) {
            for (const auto &[flag, parser] : array) {
                const auto len = std::strlen(flag);

                // flag match, we display according to a callable
                if (!std::strncmp(str.data(), flag, len))
                    return parser(str.substr(len)) + len;
            }
            // no special flag found, we just display the character
            return *s_stream << str[0], 1ul;
        };

        // main flags
        const std::array<const PairFlag, 2> FLAG_VALUE {
            PairFlag { "${info:",  [&INFO_FLAG, &check_flags](const std::string_view str) { return check_flags(str, INFO_FLAG); } },
            PairFlag { "${style:", style_parser },
        };

        return check_flags(search, FLAG_VALUE);
    };

    print_string(s_display_format);

    return *s_stream;
}

constexpr std::optional<nd::engine::Logger::PairStyle> nd::engine::Logger::get_style_value(const char *search)
{
    for (const auto &i : S_SUPPORTED_STYLE)
        if (!std::strncmp(i.first, search, std::strlen(i.first)))
            return i;
    return {};
}

constexpr std::optional<const char *> nd::engine::Logger::level_as_string(level search)
{
    for (const auto &[v, msg] : S_LEVEL_AS_STRING)
        if (search == v)
            return msg;
    return {};
}
