/**  
 * @file    instructionexeckill.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Execute the KILL instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexeckill.h"

// constructor
 InstructionExecKill::InstructionExecKill( )
{
}

// destructor
/*virtual*/ InstructionExecKill::~InstructionExecKill( )
{
}

// execute the opcode
bool InstructionExecKill::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    // kill instruction do nothing except commit suicide
    pTask->setStatus(TaskSet::TASKSET_KILLED_SUICIDE);
    return false;
}
