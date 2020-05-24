/**
 * @file    instructionexecjl.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the JL instruction
 */

#ifndef INSTRUCTION_EXEC_JL_H
#define INSTRUCTION_EXEC_JL_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJl : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJl( );
        virtual ~InstructionExecJl( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JL_H
