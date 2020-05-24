/**
 * @file    instructionexecfactory.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Instruction exec factory to select the right object to execute at runtime
 */

#ifndef INSTRUCTION_EXEC_FACTORY_H
#define INSTRUCTION_EXEC_FACTORY_H

// standard includes

// personal includes
#include "opcode.h"
#include "iinstructionexec.h"

// class definition
class InstructionExecFactory
{
    private:        // private members

    public:         // public methods

        // constructor
        InstructionExecFactory()
        { }

        // destructor
        virtual ~InstructionExecFactory()
        { }

        // return the right element
        IInstructionExec* InstructionExec(InstrOpcode_t nOpcode);
}; 
#endif // INSTRUCTION_EXEC_FACTORY_H
