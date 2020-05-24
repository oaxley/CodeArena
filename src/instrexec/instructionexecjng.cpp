/**  
 * @file    instructionexecjng.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JNG instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjng.h"

// constructor
 InstructionExecJng::InstructionExecJng( )
{
}

// destructor
/*virtual*/ InstructionExecJng::~InstructionExecJng( )
{
}

// execute the jmp opcode
bool InstructionExecJng::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if GT flag is false
    if( !pTask->getGT() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // remove flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
