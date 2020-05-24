/**  
 * @file    instructionexecjne.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JNE instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjne.h"

// constructor
 InstructionExecJne::InstructionExecJne( )
{
}

// destructor
/*virtual*/ InstructionExecJne::~InstructionExecJne( )
{
}

// execute the jmp opcode
bool InstructionExecJne::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if EQ flag is false
    if( !pTask->getEQ() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // remove flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
