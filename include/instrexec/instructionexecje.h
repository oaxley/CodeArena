/**
 * @file    instructionexecje.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the JE instruction
 */

#ifndef INSTRUCTION_EXEC_JE_H
#define INSTRUCTION_EXEC_JE_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJe : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJe( );
        virtual ~InstructionExecJe( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JE_H
