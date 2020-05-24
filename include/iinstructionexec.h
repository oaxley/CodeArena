/**
 * @file    iinstructionexec.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Interface / Virtual interface for Instruction execution routine
 */

#ifndef IINSTRUCTION_EXEC_H
#define IINSTRUCTION_EXEC_H

// standard includes
#include <string>

// personal includes
#include "settings.h"
#include "types.h"
#include "instruction.h"
#include "taskset.h"
#include "memory.h"


// class definition
class IInstructionExec
{
    public:         // public members
        enum FieldSelect_t
        {
            SOURCE_FIELD,
            DESTINATION_FIELD
        };

    public:         // public methods
        // constructor
        IInstructionExec()
        { }

        // destructor
        virtual ~IInstructionExec()
        { }

        // execute the instruction
        virtual bool execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
        { return false; }

    protected:
        // compute the block address
        virtual _uint getBlockAddress(InstrADMode_t emode, _s16 value, FieldSelect_t field, TaskSet* pTask, Memory* pMemory)
        {
            _uint nUnit = 0;
            switch(emode)
            {
                case ADMODE_DIRECT_INC:
                    nUnit = (pTask->getInitAddress() + pTask->getPC() + value) % CORE_MEMORY_SIZE;
                    break;
                case ADMODE_DIRECT_DEC:
                    nUnit = (pTask->getInitAddress() + pTask->getPC() - value) % CORE_MEMORY_SIZE;
                    break;
                case ADMODE_INDIRECT:
                    // find initial block
                    nUnit = (pTask->getInitAddress() + pTask->getPC() + value) % CORE_MEMORY_SIZE;

                    // retrieve corresponding instruction
                    Instruction *pInstr = pMemory->getBlock(nUnit)->getInstr();
                    if( pInstr )
                    {
                        if( field == SOURCE_FIELD )
                            nUnit = static_cast<_uint>(pInstr->m_nValue1 % CORE_MEMORY_SIZE);
                        else
                            nUnit = static_cast<_uint>(pInstr->m_nValue2 % CORE_MEMORY_SIZE);
                    }
                    else
                    {
                        pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_ACCESS);
                    }
            }

            return nUnit;
        }
};

#endif // IINSTRUCTION_EXEC_H
