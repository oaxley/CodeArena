/**
 * @file    instructionexecor.h
 * @author  Sebastien Legror
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the OR instruction
 */

#ifndef INSTRUCTION_EXEC_OR_H
#define INSTRUCTION_EXEC_OR_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecOr : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecOr( );
        virtual ~InstructionExecOr( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_OR_H
