/**
 * @file    instructionexecadd.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the ADD instruction
 */

#ifndef INSTRUCTION_EXEC_ADD_H
#define INSTRUCTION_EXEC_ADD_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecAdd : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecAdd( );
        virtual ~InstructionExecAdd( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_ADD_H
