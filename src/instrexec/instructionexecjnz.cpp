/**  
 * @file    instructionexecjnz.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the JNZ instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecjnz.h"

// constructor
 InstructionExecJnz::InstructionExecJnz( )
{
}

// destructor
/*virtual*/ InstructionExecJnz::~InstructionExecJnz( )
{
}

// execute the jmp opcode
bool InstructionExecJnz::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // jump only if ZF flag is false
    if( !pTask->getZF() )
        pTask->setPC( pInstr->m_nValue1 );
    else
        pTask->setPC( pTask->getPC() + 1 );

    // remove flags
    pTask->clearFlags();

    // a jump is always true
    return true;
}
