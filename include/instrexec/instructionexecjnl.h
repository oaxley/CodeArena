/**
 * @file    instructionexecjnl.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the jng instruction
 */

#ifndef INSTRUCTION_EXEC_JNL_H
#define INSTRUCTION_EXEC_JNL_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJnl : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJnl( );
        virtual ~InstructionExecJnl( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JNL_H
