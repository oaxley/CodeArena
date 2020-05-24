/**
 * @file    instructionexecsub.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the SUB instruction
 */

#ifndef INSTRUCTION_EXEC_SUB_H
#define INSTRUCTION_EXEC_SUB_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecSub : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecSub( );
        virtual ~InstructionExecSub( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_SUB_H
