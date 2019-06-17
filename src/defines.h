#ifndef DEFINES_H
#define DEFINES_H

/*
 * File: defines.h
 *
 * Author: Daratrixx
 *
 * Contributors:
 *
 * Desciption:
 * This file defines values for the offsets and values used to read and edit the save file.
 * The offset values are most likely incorrect and need to be corrected.
 * Those defines are used in the project. No hard-coded values are to be used.
 *
 */

#include <iostream>


// Type declaration
#define ID std::uint8_t
#define NUMBER std::uint8_t
#define FLAG std::uint8_t

// NULL alias
#define null NULL

// Offset within the save files
#define OFFSET_CONTINUE 0x03
#define OFFSET_CLOAK 0x0B
#define OFFSET_CURRENT_SYMBOL 0x0F
#define OFFSET_SCARF_LENGTH 0x13
#define OFFSET_CURRENT_LEVEL 0x17
#define OFFSET_COLLECTED_SYMBOLS 0x23
#define OFFSET_FOUND_HUB 0x53
#define OFFSET_FOUND_BB 0x63
#define OFFSET_FOUND_PD 0x73
#define OFFSET_FOUND_SC 0x83
#define OFFSET_FOUND_UG 0x93
#define OFFSET_FOUND_TOWER 0xA3
#define OFFSET_FOUND_LEVEL09 0xE3

// Values within the save file
#define VALUE_LEVEL_HUB 0x0
#define VALUE_LEVEL_BB 0x1
#define VALUE_LEVEL_PD 0x2
#define VALUE_LEVEL_SC 0x3
#define VALUE_LEVEL_UG 0x4
#define VALUE_LEVEL_TOWER 0x5
#define VALUE_LEVEL_SNOW 0x6
#define VALUE_LEVEL_PARADISE 0x7
#define VALUE_LEVEL_CREDITS 0x8
#define VALUE_LEVEL_LEVEL09 0x9
#define VALUE_LEVEL_CREDITS1 0xA
#define VALUE_LEVEL_CREDITS2 0xB
#define VALUE_CLOAK_1RED 0x0
#define VALUE_CLOAK_2RED 0x1
#define VALUE_CLOAK_3RED 0x2
#define VALUE_CLOAK_4RED 0x3
#define VALUE_CLOAK_2WHITE 0x4
#define VALUE_CLOAK_3WHITE 0x5
#define VALUE_CLOAK_4WHITE 0x6

#endif // DEFINES_H
