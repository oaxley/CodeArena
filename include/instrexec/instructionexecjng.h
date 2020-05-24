/**
 * @file    instructionexecjng.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the jng instruction
 */

#ifndef INSTRUCTION_EXEC_JNG_H
#define INSTRUCTION_EXEC_JNG_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJng : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJng( );
        virtual ~InstructionExecJng( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JNG_H
