/**
 * @file    instructionsetitem.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Interface / a single instruction supported by the core
 */

#ifndef INSTRUCTIONSET_ITEM_H
#define INSTRUCTIONSET_ITEM_H

// standard includes
#include <string>

// personal includes
#include "types.h"
#include "opcode.h"
#include "debug.h"

// class definition
class InstructionSetItem
{
    private:        // private members

        std::string     m_strOpcode;            // opcode string
        InstrOpcode_t   m_nOpcode;              // opcode value
        _uint           m_nParameters;          // number of parameters required for this instruction
        bool            m_bIsModifiable;        // true if modifiers are supported

    public:         // public method

        //{ xtors
        InstructionSetItem(std::string strOpcode, InstrOpcode_t nOpcode, _uint nParam, bool bModif) :
            m_strOpcode(strOpcode), m_nOpcode(nOpcode), m_nParameters(nParam), m_bIsModifiable(bModif)
        {
        }

        virtual ~InstructionSetItem( )
        {
        }
        //}

        //{ getters
        std::string getOpcodeString( ) const {
            return m_strOpcode;
        }

        InstrOpcode_t getOpcodeValue( ) const {
            return m_nOpcode;
        }

        _uint getParamsNumber( ) const {
            return m_nParameters;
        }

        bool isModifiable( ) const {
            return m_bIsModifiable;
        }
        //}
};


#endif // INSTRUCTIONSET_ITEM_H

