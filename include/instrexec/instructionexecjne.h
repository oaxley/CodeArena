/**
 * @file    instructionexecjne.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the jng instruction
 */

#ifndef INSTRUCTION_EXEC_JNE_H
#define INSTRUCTION_EXEC_JNE_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJne : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJne( );
        virtual ~InstructionExecJne( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JNE_H
