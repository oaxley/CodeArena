/**
 * @file    instructionexecnop.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Execute the KILL instruction
 */

#ifndef INSTRUCTION_EXEC_KILL_H
#define INSTRUCTION_EXEC_KILL_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class definition
class InstructionExecKill : public IInstructionExec
{
    private:        // private members

        // no copy assignation

    public:         // public methods
        InstructionExecKill( );
        virtual ~InstructionExecKill( );

        bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_KILL_H
