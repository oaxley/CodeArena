/**
 * @file    instructionexecxor.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the XOR instruction
 */

#ifndef INSTRUCTION_EXEC_XOR_H
#define INSTRUCTION_EXEC_XOR_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecXor : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecXor( );
        virtual ~InstructionExecXor( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_XOR_H
