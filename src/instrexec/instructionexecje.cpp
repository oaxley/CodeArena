/**  
 * @file    instructionexecje.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JE instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecje.h"

// constructor
 InstructionExecJe::InstructionExecJe( )
{
}

// destructor
/*virtual*/ InstructionExecJe::~InstructionExecJe( )
{
}

// execute the jmp opcode
bool InstructionExecJe::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if EQ flag is true
    if( pTask->getEQ() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // remove cmp flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
