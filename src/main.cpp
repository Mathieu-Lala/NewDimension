/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** main
*/

#include "engine/Logger.hpp"

int main()
{
    engine::Logger::set_current_level(engine::Logger::DEBUG);
    LOG(engine::Logger::CRITIC, "test");

    engine::Logger::set_current_level(engine::Logger::WARNING);
    LOG(engine::Logger::NOTICE, "wow");

    return 0;
}
