/**
 * @file    instructionexecdiv.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Interface / Execute the DIV instruction
 */

#ifndef INSTRUCTION_EXEC_DIV_H
#define INSTRUCTION_EXEC_DIV_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecDiv : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecDiv( );
        virtual ~InstructionExecDiv( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_DIV_H
