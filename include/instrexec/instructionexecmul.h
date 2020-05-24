/**
 * @file    instructionexecmul.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the MUL instruction
 */

#ifndef INSTRUCTION_EXEC_MUL_H
#define INSTRUCTION_EXEC_MUL_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecMul : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecMul( );
        virtual ~InstructionExecMul( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_MUL_H
