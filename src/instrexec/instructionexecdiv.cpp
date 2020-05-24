/**  
 * @file    instructionexecdiv.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Implementation / Execute the DIV instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexecdiv.h"

// constructor
 InstructionExecDiv::InstructionExecDiv( )
{
}

// destructor
/*virtual*/ InstructionExecDiv::~InstructionExecDiv( )
{
}

// execute the opcode
bool InstructionExecDiv::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    Instruction* pInstrDst = 0;

    // if destination is a value -> error
    if( pInstr->m_nAdMode2 == ADMODE_VALUE )
    {
        pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_OPERAND);
        return false;
    }

    // compute destination memory
    _uint nUnitDst = getBlockAddress(pInstr->m_nAdMode2, pInstr->m_nValue2, IInstructionExec::DESTINATION_FIELD, pTask, pMemory);
    if( pTask->getStatus( ) != TaskSet::TASKSET_ALIVE )
        return false;

    // check the block validity
    if( pMemory->getBlock(nUnitDst)->getStatus( ) == Block::BLOCK_EMPTY )
    {
        pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_ACCESS);
        return false;
    }
    else
        pInstrDst = pMemory->getBlock(nUnitDst)->getInstr( );

    // the source is a value
    if( pInstr->m_nAdMode1 == ADMODE_VALUE )
    {
        // check the division by zero
        if( pInstr->m_nValue1 == 0 )
        {
            pTask->setStatus(TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO);
            return false;
        }
        
        // perform the operation
        pTask->setZF(false);
        switch(pInstr->m_nModifier)
        {
            case MOD_0:
                pInstrDst->m_nOpcode = static_cast<InstrOpcode_t>((pInstrDst->m_nOpcode / pInstr->m_nValue1) % OP_COUNT_VALUE);
                break;
            case MOD_1:
                pInstrDst->m_nModifier = static_cast<InstrModifier_t>((pInstrDst->m_nModifier / pInstr->m_nValue1) % MOD_COUNT_VALUE);
                break;
            case MOD_2:
                pInstrDst->m_nAdMode1 = static_cast<InstrADMode_t>((pInstrDst->m_nAdMode1 / pInstr->m_nValue1) % ADMODE_COUNT_VALUE);
                break;
            case MOD_A:
            case MOD_3:
                pInstrDst->m_nValue1 = pInstrDst->m_nValue1 / pInstr->m_nValue1;
                if( pInstrDst->m_nValue1 == 0 )
                    pTask->setZF(true);
                break;
            case MOD_4:
                pInstrDst->m_nAdMode2 = static_cast<InstrADMode_t>((pInstrDst->m_nAdMode2 / pInstr->m_nValue1) % ADMODE_COUNT_VALUE);
                break;
            case MOD_B:
            case MOD_5:
                pInstrDst->m_nValue2 = pInstrDst->m_nValue2 / pInstr->m_nValue1; 
                if( pInstrDst->m_nValue2 == 0 )
                    pTask->setZF(true);
                break;
            default:
                pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_OPERAND);
                return false;
        }
    }
    else
    {
        // compute source memory
        _uint nUnitSrc = getBlockAddress(pInstr->m_nAdMode1, pInstr->m_nValue1, IInstructionExec::SOURCE_FIELD, pTask, pMemory);
        if( pTask->getStatus( ) != TaskSet::TASKSET_ALIVE )
            return false;

        // check source instruction
        Instruction* pInstrSrc = pMemory->getBlock(nUnitSrc)->getInstr();
        if( pInstrSrc == 0 )
        {
            pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_ACCESS);
            return false;
        }

        // perform the operation
        pTask->setZF(false);
        switch(pInstr->m_nModifier)
        {
            case MOD_3:
            case MOD_A:
                // check the division by zero
                if( pInstrSrc->m_nValue1 == 0 )
                {
                    pTask->setStatus(TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO);
                    return false;
                }
                pInstrDst->m_nValue1 = pInstrDst->m_nValue1 / pInstrSrc->m_nValue1;
                if( pInstrDst->m_nValue1 == 0 )
                    pTask->setZF(true);
                break;
            case MOD_5:
            case MOD_B:
                // check the division by zero
                if( pInstrSrc->m_nValue2 == 0 )
                {
                    pTask->setStatus(TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO);
                    return false;
                }
                pInstrDst->m_nValue2 = pInstrDst->m_nValue2 / pInstrSrc->m_nValue2;
                if( pInstrDst->m_nValue2 == 0 )
                    pTask->setZF(true);
                break;
            case MOD_AB:
                // check the division by zero
                if( pInstrSrc->m_nValue1 == 0 )
                {
                    pTask->setStatus(TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO);
                    return false;
                }
                pInstrDst->m_nValue2 = pInstrDst->m_nValue2 / pInstrSrc->m_nValue1;
                if( pInstrDst->m_nValue2 == 0 )
                    pTask->setZF(true);
                break;
            case MOD_BA:
                // check the division by zero
                if( pInstrSrc->m_nValue2 == 0 )
                {
                    pTask->setStatus(TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO);
                    return false;
                }
                pInstrDst->m_nValue1 = pInstrDst->m_nValue1 / pInstrSrc->m_nValue2;
                if( pInstrDst->m_nValue1 == 0 )
                    pTask->setZF(true);
                break;
            case MOD_X:
                // check the division by zero
                if( (pInstrSrc->m_nValue1 == 0) || (pInstrSrc->m_nValue2 == 0))
                {
                    pTask->setStatus(TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO);
                    return false;
                }
                pInstrDst->m_nValue1 = pInstrDst->m_nValue1 / pInstrSrc->m_nValue2;
                pInstrDst->m_nValue2 = pInstrDst->m_nValue2 / pInstrSrc->m_nValue1;
                if( (pInstrDst->m_nValue1 == 0) || (pInstrDst->m_nValue2 == 0) )
                    pTask->setZF(true);
                break;
            case MOD_F:
                // check the division by zero
                if( (pInstrSrc->m_nValue1 == 0) || (pInstrSrc->m_nValue2 == 0))
                {
                    pTask->setStatus(TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO);
                    return false;
                }
                pInstrDst->m_nValue1 = pInstrDst->m_nValue1 / pInstrSrc->m_nValue1;
                pInstrDst->m_nValue2 = pInstrDst->m_nValue2 / pInstrSrc->m_nValue2;
                if( (pInstrDst->m_nValue1 == 0) || (pInstrDst->m_nValue2 == 0) )
                    pTask->setZF(true);
                break;
            default:
                pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_OPERAND);
                return false;
        }
    }

    // remove cmp flags
    pTask->clearFlags();

    // increment program counter
    pTask->setPC( pTask->getPC() + 1 );

    return true;
}
