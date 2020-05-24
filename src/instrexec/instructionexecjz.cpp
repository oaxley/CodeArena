/**  
 * @file    instructionexecjz.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JZ instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjz.h"

// constructor
 InstructionExecJz::InstructionExecJz( )
{
}

// destructor
/*virtual*/ InstructionExecJz::~InstructionExecJz( )
{
}

// execute the jmp opcode
bool InstructionExecJz::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if ZF flag is true
    if( pTask->getZF() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // a jump is always true
    return true;
}
