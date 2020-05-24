/**
 * @file    instructionexecjnz.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the jng instruction
 */

#ifndef INSTRUCTION_EXEC_JNZ_H
#define INSTRUCTION_EXEC_JNZ_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJnz : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJnz( );
        virtual ~InstructionExecJnz( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JNZ_H
