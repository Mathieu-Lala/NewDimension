/*
** EPITECH PROJECT, 2019
** NewDimension
** File description:
** config
*/

#ifndef CONFIG_HPP_
# define CONFIG_HPP_

# include "config/cmake_config.h"

// Project build type release
# define Release 1
// Project build type debug
# define Debug 2

# ifndef PROJECT_BUILD_TYPE
#  define PROJECT_BUILD_TYPE Debug
# endif

// success exit status
# define ND_SUCCESS 0

// error exit status
# define ND_ERROR 84

#endif /* !CONFIG_HPP_ */
