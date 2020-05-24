/**
 * @file    instructionexecjg.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the JG instruction
 */

#ifndef INSTRUCTION_EXEC_JG_H
#define INSTRUCTION_EXEC_JG_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecJg : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecJg( );
        virtual ~InstructionExecJg( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_JG_H
