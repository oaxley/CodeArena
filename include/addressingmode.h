/**
 * @file    addressingmode.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Instruction addressing modes
 */

#ifndef ADDRESSINGMODE_H
#define ADDRESSINGMODE_H

enum InstrADMode_t
{
    ADMODE_VALUE,           // #: value
    ADMODE_DIRECT_INC,      // +: direct addressing increment
    ADMODE_DIRECT_DEC,      // -: direct addressing decrement
    ADMODE_INDIRECT,        // @: indirect addressing

    ADMODE_COUNT_VALUE,     // number of addressing mode supported

    ADMODE_NONE,
    ADMODE_DEFAULT = ADMODE_DIRECT_INC  // default mode is the direct addressing mode
};

#endif // ADDRESSINGMODE_H
