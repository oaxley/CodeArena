/**
 * @file    types.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Custom types
 */

#ifndef TYPES_H
#define TYPES_H

// standard includes

// personal includes
#include <oaxlib/oaxlib.h>

// we redefine types from oaxlib::types to avoid the "usage namespace oaxlib"
// in the interface files

typedef uint8_t     _u8;
typedef uint16_t    _u16;
typedef uint32_t    _u32;

typedef int8_t      _s8;
typedef int16_t     _s16;
typedef int32_t     _s32;

typedef uint_t     _uint;
typedef uchar_t    _uchar;

#endif // TYPES_H

