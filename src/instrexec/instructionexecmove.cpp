/**
 * @file    instructionexecmove.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-21
 *
 * @brief   Implementation / Execute the MOVE instruction
 */

// standard includes
#include <iostream>

// personal includes
#include "instrexec/instructionexecmove.h"
#include "debug.h"

// constructor
 InstructionExecMove::InstructionExecMove( ) :
    IInstructionExec()
{
    DEBUG_ENTER_METHOD
}

// destructor
/* virtual */
 InstructionExecMove::~InstructionExecMove( )
{
    DEBUG_ENTER_METHOD
}

// execute the MOVE instruction
/* virtual */
bool InstructionExecMove::execute(Instruction* pInstr, TaskSet* pTask, Memory* pMemory)
{
    DEBUG_ENTER_METHOD

    // if destination is a value -> error
    if( pInstr->m_nAdMode2 == ADMODE_VALUE )
    {
        pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_OPERAND);
        return false;
    }

    // compute destination memory
    Instruction* pInstrDst = 0;
    _uint nUnitDst = getBlockAddress(pInstr->m_nAdMode2, pInstr->m_nValue2, IInstructionExec::DESTINATION_FIELD, pTask, pMemory);
    if( pTask->getStatus( ) != TaskSet::TASKSET_ALIVE )
        return false;

    // check the block validity
    if( pMemory->getBlock(nUnitDst)->getStatus( ) == Block::BLOCK_EMPTY )
    {
        // create a new instruction here
        pInstrDst = new Instruction;
    }
    else
        pInstrDst = pMemory->getBlock(nUnitDst)->getInstr( );

    if( pInstr->m_nAdMode1 == ADMODE_VALUE )
    {
        // store the value at the right place
        switch(pInstr->m_nModifier)
        {
            case MOD_0:
                pInstrDst->m_nOpcode = static_cast<InstrOpcode_t>(pInstr->m_nValue1 % OP_COUNT_VALUE);
                break;
            case MOD_1:
                pInstrDst->m_nModifier = static_cast<InstrModifier_t>(pInstr->m_nValue1 % MOD_COUNT_VALUE);
                break;
            case MOD_2:
                pInstrDst->m_nAdMode1 = static_cast<InstrADMode_t>(pInstr->m_nValue1 % ADMODE_COUNT_VALUE);
                break;
            case MOD_A:
            case MOD_3:
                pInstrDst->m_nValue1 = pInstr->m_nValue1;
                break;
            case MOD_4:
                pInstrDst->m_nAdMode2 = static_cast<InstrADMode_t>(pInstr->m_nValue1 % ADMODE_COUNT_VALUE);
                break;
            case MOD_B:
            case MOD_5:
                pInstrDst->m_nValue2 = pInstr->m_nValue1;
                break;
            default:
                // delete the destination instruction if we created on purpose
                if( pMemory->getBlock(nUnitDst)->getStatus( ) == Block::BLOCK_EMPTY )
                    delete pInstrDst;
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

        Instruction* pInstrSrc = pMemory->getBlock(nUnitSrc)->getInstr();
        if( pInstrSrc == 0 )
        {
            pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_ACCESS);

            // delete the destination instruction
            if( pMemory->getBlock(nUnitDst)->getStatus( ) == Block::BLOCK_EMPTY )
                delete pInstrDst;

            return false;
        }

        // store the value at the right place
        switch(pInstr->m_nModifier)
        {
            case MOD_A:
                pInstrDst->m_nAdMode1 = pInstrSrc->m_nAdMode1;
                pInstrDst->m_nValue1  = pInstrSrc->m_nValue1;
                break;
            case MOD_B:
                pInstrDst->m_nAdMode2 = pInstrSrc->m_nAdMode2;
                pInstrDst->m_nValue2  = pInstrSrc->m_nValue2;
                break;
            case MOD_AB:
                pInstrDst->m_nAdMode2 = pInstrSrc->m_nAdMode1;
                pInstrDst->m_nValue2  = pInstrSrc->m_nValue1;
                break;
            case MOD_BA:
                pInstrDst->m_nAdMode1 = pInstrSrc->m_nAdMode2;
                pInstrDst->m_nValue1  = pInstrSrc->m_nValue2;
                break;
            case MOD_X:
                pInstrDst->m_nAdMode1 = pInstrSrc->m_nAdMode2;
                pInstrDst->m_nValue1  = pInstrSrc->m_nValue2;
                pInstrDst->m_nAdMode2 = pInstrSrc->m_nAdMode1;
                pInstrDst->m_nValue2  = pInstrSrc->m_nValue1;
                break;
            case MOD_F:
                pInstrDst->m_nAdMode1 = pInstrSrc->m_nAdMode1;
                pInstrDst->m_nValue1  = pInstrSrc->m_nValue1;
                pInstrDst->m_nAdMode2 = pInstrSrc->m_nAdMode2;
                pInstrDst->m_nValue2  = pInstrSrc->m_nValue2;
                break;
            case MOD_I:
                pInstrDst->m_nOpcode   = pInstrSrc->m_nOpcode;
                pInstrDst->m_nModifier = pInstrSrc->m_nModifier;
                pInstrDst->m_nAdMode1  = pInstrSrc->m_nAdMode1;
                pInstrDst->m_nValue1   = pInstrSrc->m_nValue1;
                pInstrDst->m_nAdMode2  = pInstrSrc->m_nAdMode2;
                pInstrDst->m_nValue2   = pInstrSrc->m_nValue2;
                break;
            case MOD_0:
                pInstrDst->m_nOpcode   = pInstrSrc->m_nOpcode;
                break;
            case MOD_1:
                pInstrDst->m_nModifier = pInstrSrc->m_nModifier;
                break;
            case MOD_2:
                pInstrDst->m_nAdMode1  = pInstrSrc->m_nAdMode1;
                break;
            case MOD_3:
                pInstrDst->m_nValue1   = pInstrSrc->m_nValue1;
                break;
            case MOD_4:
                pInstrDst->m_nAdMode2  = pInstrSrc->m_nAdMode2;
                break;
            case MOD_5:
                pInstrDst->m_nValue2   = pInstrSrc->m_nValue2;
                break;
        }
    }

    // attach the instruction to the block
    pMemory->getBlock(nUnitDst)->setInstr(pInstrDst);
    pMemory->getBlock(nUnitDst)->setTaskSet(pTask);

    // remove flags
    pTask->clearFlags();
    pTask->setZF(false);

    // increase the program counter
    pTask->setPC( pTask->getPC( ) + 1 );

    return true;
}
