/**  
 * @file    instructionexecnop.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the NOP instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecnop.h"

// constructor
 InstructionExecNop::InstructionExecNop( )
{
}

// destructor
/*virtual*/ InstructionExecNop::~InstructionExecNop( )
{
}

// execute the opcode
bool InstructionExecNop::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // remove cmp flags
    pTask->clearFlags();

    // NOP instruction do nothing
    pTask->setPC( pTask->getPC() + 1);
    return true;
}
