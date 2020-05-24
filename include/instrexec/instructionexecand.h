/**
 * @file    instructionexecand.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the AND instruction
 */

#ifndef INSTRUCTION_EXEC_AND_H
#define INSTRUCTION_EXEC_AND_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecAnd : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecAnd( );
        virtual ~InstructionExecAnd( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_AND_H
