/**  
 * @file    instructionexecjg.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JG instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjg.h"

// constructor
 InstructionExecJg::InstructionExecJg( )
{
}

// destructor
/*virtual*/ InstructionExecJg::~InstructionExecJg( )
{
}

// execute the jmp opcode
bool InstructionExecJg::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if GT flag is true
    if( pTask->getGT() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // remove cmp flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
