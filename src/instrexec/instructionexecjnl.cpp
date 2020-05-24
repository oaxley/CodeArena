/**  
 * @file    instructionexecjnl.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JNL instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjnl.h"

// constructor
 InstructionExecJnl::InstructionExecJnl( )
{
}

// destructor
/*virtual*/ InstructionExecJnl::~InstructionExecJnl( )
{
}

// execute the jmp opcode
bool InstructionExecJnl::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if LT flag is false
    if( !pTask->getLT() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // remove flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
