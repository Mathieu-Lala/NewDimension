/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** Logger
*/

#include <fstream>
#include <ctime>
#include <functional>
#include <cstring>
#include "engine/Logger.hpp"

std::ostream *engine::Logger::s_stream = engine::Logger::DEFAULT_STREAM;

engine::Logger::level engine::Logger::s_current_level = engine::Logger::DEFAULT_LEVEL;

engine::Logger::uid engine::Logger::s_current_msg_uid = 0ul;

std::string engine::Logger::s_display_format("${timestamp} ${uid} [${level}] file:${file} line:${line} func:${func} : ");

bool engine::Logger::set_stream(const std::string_view filepath)
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

std::ostream &engine::Logger::get_stream()
{
    if (!s_stream)
        std::runtime_error("engine::Logger #no stream set#");
    return *s_stream;
}

engine::Logger::level engine::Logger::get_current_level() noexcept
{
    return s_current_level;
}

void engine::Logger::set_current_level(level new_level) noexcept
{
    s_current_level = new_level;
}

void engine::Logger::set_format(const std::string &format) noexcept
{
    s_display_format = format;
}

std::ostream &engine::Logger::dump_info(level msg_level, const char *file, int line, const char *func)
{
    if (!s_stream)
        throw std::runtime_error("engine::Logger #no stream set#");

    const auto level_as_string = [](level search) {
        for (const auto &[v, msg] : S_LEVEL_AS_STRING)
            if (search == v)
                return msg;
        return "UNKNOWN";
    };

    const auto check_flags = [&](const std::string_view search) {
        const std::array<const std::pair<const char *, const std::function<void()>>, 7> FORMAT_PARSER = {
            std::make_pair("$",           [&]() { *s_stream << "$"; }),
            std::make_pair("{timestamp}", [&]() { *s_stream << std::time(nullptr); }),
            std::make_pair("{uid}",       [&]() { *s_stream << s_current_msg_uid++; }),
            std::make_pair("{level}",     [&]() { *s_stream << level_as_string(msg_level); }),
            std::make_pair("{file}",      [&]() { *s_stream << file; }),
            std::make_pair("{line}",      [&]() { *s_stream << line; }),
            std::make_pair("{func}",      [&]() { *s_stream << func; }),
        };

        for (const auto &[flag, parser] : FORMAT_PARSER)
            if (std::strncmp(search.data(), flag, std::strlen(flag)) == 0)
                return parser(), std::strlen(flag);
        return 0ul;
    };

    for (std::size_t i = 0ul; i != s_display_format.size(); i++)
        if (s_display_format[i] == '$')
            i += check_flags(s_display_format.data() + i + 1);
        else
            *s_stream << s_display_format[i];

    return *s_stream;
}
