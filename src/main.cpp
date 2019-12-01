/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** main
*/

#include "engine/Logger.hpp"
#include "config/config.hpp"

int main(int, char **av)
{
    NOTICE(
        "project name: " << PROJECT_NAME <<
        "version: " <<
        PROJECT_VERSION_MAJOR << "." <<
        PROJECT_VERSION_MINOR << "." <<
        PROJECT_VERSION_PATCH << " " <<
        "build type: " << PROJECT_BUILD_TYPE
    );

    int i = 0;
    DEBUG("i= " << i);

    return ND_SUCCESS;
}
