/**
 * @file    opcode.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Instruction opcode list
 */

#ifndef OPCODE_H
#define OPCODE_H

enum InstrOpcode_t
{
    OP_MOVE,

    OP_JMP,
    OP_JZ,
    OP_JNZ,
    OP_JG,
    OP_JNG,
    OP_JE,
    OP_JNE,
    OP_JL,
    OP_JNL,

    OP_CMP,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,

    OP_AND,
    OP_OR,
    OP_XOR,
    OP_NOT,

    OP_NOP,
    OP_KILL,

    OP_COUNT_VALUE,     // number of opcodes supported
    OP_UNKNOWN
};

#endif // OPCODE_H

