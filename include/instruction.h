/**
 * @file    instruction.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Interface / Compiled instruction hold in a block of memory
 */

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// standard includes
#include <vector>

// personal includes
#include "types.h"
#include "debug.h"
#include "addressingmode.h"
#include "modifier.h"
#include "opcode.h"

// class definition
class Instruction
{
    public:         // public members

        // everything is public to avoid the necessity of accessors
        // TODO: change that!
        InstrOpcode_t       m_nOpcode;      // instruction opcode
        InstrModifier_t     m_nModifier;    // instruction modifier
        InstrADMode_t       m_nAdMode1;     // operand #1 - addressing mode
        _s16                m_nValue1;      // operand #1 - value
        InstrADMode_t       m_nAdMode2;     // operand #2 - addressing mode
        _s16                m_nValue2;      // operand #2 - value

        // constructor
        Instruction( ) :
            m_nOpcode(OP_UNKNOWN), m_nModifier(MOD_NONE), m_nAdMode1(ADMODE_NONE), m_nValue1(0),
            m_nAdMode2(ADMODE_NONE), m_nValue2(0)
        {
            DEBUG_ENTER_METHOD
        }

        // destructor
        virtual ~Instruction( ) {
            DEBUG_ENTER_METHOD
            m_nOpcode   = OP_UNKNOWN;
            m_nModifier = MOD_NONE;
            m_nAdMode1  = ADMODE_NONE;
            m_nValue1   = 0;
            m_nAdMode2  = ADMODE_NONE;
            m_nValue2   = 0;
        }

        // copy constructor
        Instruction(const Instruction& rOther) {
            DEBUG_ENTER_METHOD

            m_nOpcode   = rOther.m_nOpcode;
            m_nModifier = rOther.m_nModifier;
            m_nAdMode1  = rOther.m_nAdMode1;
            m_nValue1   = rOther.m_nValue1;
            m_nAdMode2  = rOther.m_nAdMode2;
            m_nValue2   = rOther.m_nValue2;
        }

        // assignment constructor
        Instruction& operator=(const Instruction& rOther) {
            DEBUG_ENTER_METHOD

            if( this == &rOther )
                return *this;

            m_nOpcode   = rOther.m_nOpcode;
            m_nModifier = rOther.m_nModifier;
            m_nAdMode1  = rOther.m_nAdMode1;
            m_nValue1   = rOther.m_nValue1;
            m_nAdMode2  = rOther.m_nAdMode2;
            m_nValue2   = rOther.m_nValue2;

            return *this;
        }
};

// instruction flow type & its iterator
typedef std::vector<Instruction*> vecInstructionFlow_t;
typedef std::vector<Instruction*>::iterator vecInstructionFlowIt_t;

#endif // INSTRUCTION_H

