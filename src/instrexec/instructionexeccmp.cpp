/**  
 * @file    instructionexeccmp.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2012-01-03
 *
 * @brief   Implementation / Execute the CMP instruction
 */

// standard includes

// personal includes
#include "instrexec/instructionexeccmp.h"

// constructor
 InstructionExecCmp::InstructionExecCmp( )
{
}

// destructor
/*virtual*/ InstructionExecCmp::~InstructionExecCmp( )
{
}

// execute the opcode
bool InstructionExecCmp::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    int nSrcValue, nDstValue;

    // select the source value
    if( pInstr->m_nAdMode1 == ADMODE_VALUE )
    {
        nSrcValue = pInstr->m_nValue1;
    }
    else
    {
        // retrieve the source value from the address 
        _uint nUnitSrc = getBlockAddress(pInstr->m_nAdMode1, pInstr->m_nValue1, IInstructionExec::SOURCE_FIELD, pTask, pMemory);
        if( pTask->getStatus( ) != TaskSet::TASKSET_ALIVE )
            return false;

        // check block availability
        Instruction* pInstrSrc = 0;
        if( pMemory->getBlock(nUnitSrc)->getStatus( ) == Block::BLOCK_EMPTY )
        {
            pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_ACCESS);
            return false;
        }
        else
            pInstrSrc = pMemory->getBlock(nUnitSrc)->getInstr( );

        // retrieve value depending on the modifier
        switch(pInstr->m_nModifier)
        {
            case MOD_0:
                nSrcValue = pInstrSrc->m_nOpcode;
                break;
            case MOD_1:
                nSrcValue = pInstrSrc->m_nModifier;
                break;
            case MOD_2:
                nSrcValue = pInstrSrc->m_nAdMode1;
                break;
            case MOD_AB:
            case MOD_A:
            case MOD_3:
                nSrcValue = pInstrSrc->m_nValue1;
                break;
            case MOD_4:
                nSrcValue = pInstrSrc->m_nAdMode2;
                break;
            case MOD_BA:
            case MOD_B:
            case MOD_5:
                nSrcValue = pInstrSrc->m_nValue2;
                break;
            default:
                pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_OPERAND);
                return false;
        }
    }

    // select the destination value
    if( pInstr->m_nAdMode2 == ADMODE_VALUE )
    {
        nDstValue = pInstr->m_nValue2;
    }
    else
    {
        // retrieve the destination value from the address
        _uint nUnitDst = getBlockAddress(pInstr->m_nAdMode2, pInstr->m_nValue2, IInstructionExec::DESTINATION_FIELD, pTask, pMemory);
        if( pTask->getStatus( ) != TaskSet::TASKSET_ALIVE )
            return false;

        // check block availability
        Instruction* pInstrDst = 0;
        if( pMemory->getBlock(nUnitDst)->getStatus( ) == Block::BLOCK_EMPTY )
        {
            pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_ACCESS);
            return false;
        }
        else
            pInstrDst = pMemory->getBlock(nUnitDst)->getInstr( );

        // retrieve value depending on the modifier
        switch(pInstr->m_nModifier)
        {
            case MOD_0:
                nDstValue = pInstrDst->m_nOpcode;
                break;
            case MOD_1:
                nDstValue = pInstrDst->m_nModifier;
                break;
            case MOD_2:
                nDstValue = pInstrDst->m_nAdMode1;
                break;
            case MOD_BA:
            case MOD_A:
            case MOD_3:
                nDstValue = pInstrDst->m_nValue1;
                break;
            case MOD_4:
                nDstValue = pInstrDst->m_nAdMode2;
                break;
            case MOD_AB:
            case MOD_B:
            case MOD_5:
                nDstValue = pInstrDst->m_nValue2;
                break;
            default:
                pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_OPERAND);
                return false;
        }
    }

    // make the comparison
    int nCompare = nDstValue - nSrcValue;
    if( nCompare == 0 )
        pTask->setEQ(true);
    else
        pTask->setEQ(false);

    if( nCompare < 0 )
        pTask->setGT(true);
    else
        pTask->setGT(false);

    if( nCompare > 0 )
        pTask->setLT(true);
    else
        pTask->setLT(false);

    // increment program counter
    pTask->setPC( pTask->getPC() + 1 );

    return true;
}
