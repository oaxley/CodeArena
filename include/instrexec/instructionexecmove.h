/**
 * @file    instructionexecmove.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-21
 *
 * @brief   Interface / Execute the MOVE instruction
 */

#ifndef INSTRUCTION_EXEC_MOVE_H
#define INSTRUCTION_EXEC_MOVE_H

// standard includes

// personal includes
#include "iinstructionexec.h"

// class defintion
class InstructionExecMove : public IInstructionExec
{
    private:        // private members

    public:         // public methods
        // constructor
        InstructionExecMove( );

        // destructor
        virtual ~InstructionExecMove( );

        // execute the instruction
        virtual bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory);
};

#endif // INSTRUCTION_EXEC_MOVE_H
