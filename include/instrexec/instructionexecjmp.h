/**
 * @file    instructionexecjmp.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the JMP instruction
 */

#ifndef INSTRUCTION_EXEC_JMP_H
#define INSTRUCTION_EXEC_JMP_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJmp : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJmp( );
        virtual ~InstructionExecJmp( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JMP_H
