/**
 * @file    modifier.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Instruction modifier list
 */

#ifndef MODIFIER_H
#define MODIFIER_H

enum InstrModifier_t
{
    MOD_0,            // opcode
    MOD_1,            // modifier
    MOD_2,            // argument A addressing mode
    MOD_3,            // argument A value
    MOD_4,            // argument B addressing mode
    MOD_5,            // argument B value
    MOD_A,            // dst A = src A
    MOD_B,            // dst B = src B
    MOD_AB,           // dst B = src A
    MOD_BA,           // dst A = src B
    MOD_X,            // dst A = src B & dst B = src A
    MOD_F,            // dst A = src A & dst B = src B
    MOD_I,            // instruction B = instruction A

    MOD_COUNT_VALUE,    // number of modifiers supported
    MOD_NONE

};


#endif // MODIFIER_H
