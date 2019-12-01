/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** main
*/

#include "engine/Logger.hpp"

void test_logger(const char *msg)
{
    DEBUG("debug " << msg);
    INFO("info " << msg);
    NOTICE("notice " << msg);
    WARNING("warning " << msg);
    ERROR("error " << msg);
    ALERT("alert " << msg);
    CRITIC("critic " << msg);
    EMERGENCY("emergency " << msg);

    std::cout << std::endl;

    nd::engine::Logger::set_current_level(nd::engine::Logger::ERROR);

    DEBUG("this should not be printed");
    INFO("this should not be printed");
    NOTICE("this should not be printed");
    WARNING("this should not be printed");
    ERROR("error2 " << msg);
    ALERT("alert2 " << msg);
    CRITIC("critic2 " << msg);
    EMERGENCY("emergency2 " << msg);
}

int main(int, char **av)
{
    test_logger(av[0]);

    return 0;
}
