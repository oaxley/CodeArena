/**
 * @file	settings.h
 * @author	Sebastien Legrand
 * @email	oaxley@gmail.com
 * @date	2011-12-04
 *
 * @brief	Internal program settings not found in the configuration file
 */

#ifndef SETTINGS_H
#define SETTINGS_H

//--------------------------
// main.cpp
//--------------------------

// Program return values
#define PROGRAM_SUCCESSFULL         0
#define PROGRAM_INVALID_ARGS_COUNT  2


//--------------------------
// core.cpp
//--------------------------

// number of "gladiators"
#define NB_GLADIATORS               2

// number of memory blocks
#define CORE_MEMORY_SIZE            4096

// number max of core cycle per game
#define CORE_MAX_CYCLES             100000

//--------------------------
// parser.cpp
//--------------------------

// define the maximum number of characters in a code line
#define MAX_CHARS                   256

//--------------------------
// display.cpp
//--------------------------

// screen max dimension
#define SCREEN_MAX_X                130
#define SCREEN_MAX_Y                43

// main board dimension = screen dimension
#define MAINBOARD_MAX_X             SCREEN_MAX_X
#define MAINBOARD_MAX_Y             SCREEN_MAX_Y
#define MAINBOARD_VLINE_1           64
#define MAINBOARD_VLINE_2           65


// memory zone dimension (4096 = 128x32)
#define MEMORY_ZONE_MAX_X           128
#define MEMORY_ZONE_MAX_Y           32

// gladiator #1 dimension
#define GLADIATOR_ONE_MAX_X         MAINBOARD_VLINE_1-1
#define GLADIATOR_ONE_MAX_Y         8

// gladiator #2 dimension
#define GLADIATOR_TWO_MAX_X         GLADIATOR_ONE_MAX_X         // makes the 2 zones equals
#define GLADIATOR_TWO_MAX_Y         8

#endif // SETTINGS_H
