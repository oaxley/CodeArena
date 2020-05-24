/**
 * @file    instructionset.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Interface / InstructionSet Object
 */

#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

// standard includes
#include <string>
#include <vector>

// personal includes
#include "types.h"
#include "addressingmode.h"
#include "modifier.h"
#include "instructionsetitem.h"
#include "instruction.h"
#include "instructionexecfactory.h"
#include "memory.h"
#include "taskset.h"

// class definition
class InstructionSet
{
    private:    // private members

        typedef std::vector< InstructionSetItem* > vecOpcodeList_t;
        typedef std::vector< std::pair<std::string, InstrModifier_t> > vecModifierList_t;
        typedef std::vector< std::pair<std::string, InstrADMode_t> > vecADModeList_t;

        vecOpcodeList_t     m_vOpcodeList;      // vector containing opcode list
        vecModifierList_t   m_vModifierList;    // vector containing modifier list
        vecADModeList_t     m_vADModeList;      // vector containing addressing mode list

        std::string m_strDelims;                // delimiters string

        InstructionExecFactory m_cInstrExecFactory;

    private:    // private methods
        // initialize vectors
        void InitVectors( );

    public:     // public methods
        InstructionSet( );                  ///< constructor
        virtual ~InstructionSet( );         ///< destructor

        std::string getDelimitersList( ) const;

        //{ opcode getters
        std::string getOpcode(InstrOpcode_t value);
        InstrOpcode_t getOpcode(std::string strOpcode);
        const InstructionSetItem* getInstructionSetItem(InstrOpcode_t value);
        const InstructionSetItem* getInstructionSetItem(std::string strOpcode);
        //}

        //{ modifier getters
        std::string getModifier(InstrModifier_t value);
        InstrModifier_t getModifier(std::string strModifier);
        //}

        //{ admode getters
        std::string getADMode(InstrADMode_t value);
        InstrADMode_t getADMode(std::string strADMode);
        //}

        //{ disassemble an instruction
        std::string disassemble(Instruction* pInstr);
        //}

        //{ execute an instruction (true: execution OK)
        bool execute(TaskSet* pTask, Memory* pMemory); 
        //}
};

#endif // INSTRUCTIONSET_H

