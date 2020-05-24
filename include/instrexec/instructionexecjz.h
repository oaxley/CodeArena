/**
 * @file    instructionexecjz.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the JZ instruction
 */

#ifndef INSTRUCTION_EXEC_JZ_H
#define INSTRUCTION_EXEC_JZ_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJz : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJz( );
        virtual ~InstructionExecJz( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JZ_H
