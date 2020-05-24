/**  
 * @file    instructionexecjl.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JL instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjl.h"

// constructor
 InstructionExecJl::InstructionExecJl( )
{
}

// destructor
/*virtual*/ InstructionExecJl::~InstructionExecJl( )
{
}

// execute the jmp opcode
bool InstructionExecJl::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if LT flag is true
    if( pTask->getLT() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // remove cmp flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
