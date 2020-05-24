/**
 * @file    block.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-27
 *
 * @brief   Interface / Single memory unit that contains an instruction
 */

#ifndef BLOCK_H
#define BLOCK_H

// standard includes
#include <iostream>

// personal includes
#include "types.h"
#include "instruction.h"
#include "taskset.h"

// debug functions
#include "debug.h"

// class definition
class Block
{
    public:     // public members
        enum BlockStatus_t
        {
            BLOCK_EMPTY = 0,    // no one in this block
            BLOCK_USED          // block is taken (check the player then)
        };

    public:     // public methods

        // constructor
        Block( ) :
            m_pInstr(0), m_eBlockStatus(BLOCK_EMPTY), m_pTaskSet(0) {
            DEBUG_ENTER_METHOD
        }

        // destructor
        virtual ~Block( ) {
            DEBUG_ENTER_METHOD
        }

    //{ instruction set/get
        Instruction* getInstr( ) const {
            DEBUG_ENTER_METHOD
            return m_pInstr;
        }
        void setInstr(Instruction* pInstr) {
            DEBUG_ENTER_METHOD
            m_pInstr = pInstr;
            m_eBlockStatus = BLOCK_USED;
        }
    //}

    //{ TaskSet set/get
        TaskSet* getTaskSet( ) const {
            DEBUG_ENTER_METHOD
            return m_pTaskSet;
        }
        void setTaskSet(TaskSet* pTaskSet) {
            DEBUG_ENTER_METHOD
            m_pTaskSet = pTaskSet;
        }
    //}

    //{ block status
        BlockStatus_t getStatus( ) const {
            DEBUG_ENTER_METHOD
            return m_eBlockStatus;
        }
        void setStatus(BlockStatus_t eStatus) {
            DEBUG_ENTER_METHOD
            m_eBlockStatus = eStatus;
        }
    //}

    private:        // private members
        Instruction*    m_pInstr;           // instruction in this block
        BlockStatus_t   m_eBlockStatus;     // check the block status
        TaskSet*        m_pTaskSet;         // player holding this block

};

#endif // BLOCK_H

