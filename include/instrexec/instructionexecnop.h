/**
 * @file    instructionexecnop.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the NOP instruction
 */

#ifndef INSTRUCTION_EXEC_NOP_H
#define INSTRUCTION_EXEC_NOP_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecNop : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecNop( );
        virtual ~InstructionExecNop( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_NOP_H
