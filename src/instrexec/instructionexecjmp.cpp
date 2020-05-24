/**  
 * @file    instructionexecjmp.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JMP instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjmp.h"

// constructor
 InstructionExecJmp::InstructionExecJmp( )
{
}

// destructor
/*virtual*/ InstructionExecJmp::~InstructionExecJmp( )
{
}

// execute the jmp opcode
bool InstructionExecJmp::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // replace the PC by the new value
    pTask->setPC( pInstr->m_nValue1 );

    // remove cmp flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
