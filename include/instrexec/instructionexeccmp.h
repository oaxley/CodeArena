/**
 * @file    instructionexeccmp.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the CMP instruction
 */

#ifndef INSTRUCTION_EXEC_CMP_H
#define INSTRUCTION_EXEC_CMP_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecCmp : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecCmp( );
        virtual ~InstructionExecCmp( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_CMP_H
