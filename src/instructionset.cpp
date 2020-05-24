/**
 * @file    instructionset.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Implementation / InstructionSet Object
 */

// standard includes
#include <iostream>
#include <sstream>

// personal includes
#include "debug.h"
#include "instructionset.h"
#include "iinstructionexec.h"

//{ private methods
void InstructionSet::InitVectors( )
{
    DEBUG_ENTER_METHOD

    InstructionSetItem* pItem = 0;

    // create opcode list
    pItem = new InstructionSetItem(std::string("MOVE"), OP_MOVE, 4, true); m_vOpcodeList.push_back(pItem);

    pItem = new InstructionSetItem(std::string("JMP"), OP_JMP, 2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JZ"),  OP_JZ,  2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JNZ"), OP_JNZ, 2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JE"),  OP_JE,  2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JNE"), OP_JNE, 2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JG"),  OP_JG,  2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JNG"), OP_JNG, 2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JL"),  OP_JL,  2, false); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("JNL"), OP_JNL, 2, false); m_vOpcodeList.push_back(pItem);

    pItem = new InstructionSetItem(std::string("CMP"), OP_CMP, 4, true); m_vOpcodeList.push_back(pItem);

    pItem = new InstructionSetItem(std::string("ADD"), OP_ADD, 4, true); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("SUB"), OP_SUB, 4, true); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("MUL"), OP_MUL, 4, true); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("DIV"), OP_DIV, 4, true); m_vOpcodeList.push_back(pItem);

    pItem = new InstructionSetItem(std::string("AND"), OP_AND, 4, true); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("OR"),  OP_OR,  4, true); m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("XOR"), OP_XOR, 4, true); m_vOpcodeList.push_back(pItem);
//    pItem = new InstructionSetItem(std::string("NOT"), OP_NOT, 3, true); m_vOpcodeList.push_back(pItem);

    pItem = new InstructionSetItem(std::string("NOP"),  OP_NOP, 1, false);m_vOpcodeList.push_back(pItem);
    pItem = new InstructionSetItem(std::string("KILL"), OP_KILL,1, false);m_vOpcodeList.push_back(pItem);

    // create the modifier list
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("0"),  MOD_0) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("1"),  MOD_1) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("2"),  MOD_2) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("3"),  MOD_3) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("4"),  MOD_4) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("5"),  MOD_5) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("A"),  MOD_A) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("B"),  MOD_B) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("AB"), MOD_AB) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("BA"), MOD_BA) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("X"),  MOD_X) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("F"),  MOD_F) );
    m_vModifierList.push_back( std::pair<std::string,InstrModifier_t>(std::string("I"),  MOD_I) );

    // create the addressing mode list
    m_vADModeList.push_back( std::pair<std::string,InstrADMode_t>(std::string("#"), ADMODE_VALUE) );
    m_vADModeList.push_back( std::pair<std::string,InstrADMode_t>(std::string("+"), ADMODE_DIRECT_INC) );
    m_vADModeList.push_back( std::pair<std::string,InstrADMode_t>(std::string("-"), ADMODE_DIRECT_DEC) );
    m_vADModeList.push_back( std::pair<std::string,InstrADMode_t>(std::string("@"), ADMODE_INDIRECT) );
}
//}

//{ xtors
 InstructionSet::InstructionSet( )
{
    DEBUG_ENTER_METHOD

    InitVectors( );

    // set delimiters list
    m_strDelims=std::string(" \t,.:");
}

/*virtual*/ InstructionSet::~InstructionSet( )
{
    DEBUG_ENTER_METHOD

    // destroy all InstructionSetItem
    vecOpcodeList_t::iterator it;
    for(it = m_vOpcodeList.begin(); it != m_vOpcodeList.end(); it++)
        delete *it;

}
//}

std::string InstructionSet::getDelimitersList( ) const
{
    DEBUG_ENTER_METHOD
    return m_strDelims;
}

//{ opcode getters
std::string InstructionSet::getOpcode(InstrOpcode_t value)
{
    DEBUG_ENTER_METHOD

    vecOpcodeList_t::iterator it = m_vOpcodeList.begin();
    while( it != m_vOpcodeList.end() ) {
        if( ((*it)->getOpcodeValue()) == value )
            return (*it)->getOpcodeString();
        it++;
    }
    return std::string("XXXX");
}

InstrOpcode_t InstructionSet::getOpcode(std::string strOpcode)
{
    DEBUG_ENTER_METHOD
    InstrOpcode_t eResult = OP_UNKNOWN;
    vecOpcodeList_t::iterator it = m_vOpcodeList.begin();
    bool isDone = false;

    while( !isDone )
    {
        if( strOpcode.compare((*it)->getOpcodeString()) == 0 ) {
            isDone = true;
            eResult = (*it)->getOpcodeValue();
        } else {
            it++;
            if( it != m_vOpcodeList.end() )
                continue;
            else
                isDone = true;
        }
    }

    return eResult;
}

const InstructionSetItem* InstructionSet::getInstructionSetItem(InstrOpcode_t value)
{
    DEBUG_ENTER_METHOD
    vecOpcodeList_t::iterator it = m_vOpcodeList.begin();
    while( it != m_vOpcodeList.end() ) {
        if( (*it)->getOpcodeValue() == value )
            return *it;
        it++;
    }
    return NULL;
}

const InstructionSetItem* InstructionSet::getInstructionSetItem(std::string strOpcode)
{
    DEBUG_ENTER_METHOD
    vecOpcodeList_t::iterator it = m_vOpcodeList.begin();
    while( it != m_vOpcodeList.end() ) {
        if( strOpcode.compare((*it)->getOpcodeString()) == 0 )
            return *it;
        it++;
    }

    return NULL;
}
//}

//{ modifier getters
std::string InstructionSet::getModifier(InstrModifier_t value)
{
    DEBUG_ENTER_METHOD
    vecModifierList_t::iterator it = m_vModifierList.begin();
    while( it != m_vModifierList.end() ) {
        if( (*it).second == value )
            return (*it).first;
        it++;
    }
    return std::string("?");
}

InstrModifier_t InstructionSet::getModifier(std::string strModifier)
{
    DEBUG_ENTER_METHOD
    vecModifierList_t::iterator it = m_vModifierList.begin();
    while( it != m_vModifierList.end() ) {
        if( strModifier.compare((*it).first) == 0 )
            return (*it).second;
        it++;
    }
    return MOD_NONE;
}
//}

//{ admode getters
std::string InstructionSet::getADMode(InstrADMode_t value)
{
    DEBUG_ENTER_METHOD
    vecADModeList_t::iterator it = m_vADModeList.begin();
    while( it != m_vADModeList.end() ) {
        if( (*it).second == value )
            return (*it).first;
        it++;
    }
    return std::string("?");
}

InstrADMode_t InstructionSet::getADMode(std::string strADMode)
{
    DEBUG_ENTER_METHOD
    vecADModeList_t::iterator it = m_vADModeList.begin();
    while( it != m_vADModeList.end() ) {
        if( strADMode.compare((*it).first) == 0 )
            return (*it).second;
        it++;
    }
    return ADMODE_NONE;
}
//}

//{ disassemble an instruction
std::string InstructionSet::disassemble(Instruction* pInstr)
{
    DEBUG_ENTER_METHOD
    std::string result("");
    std::ostringstream v1,v2;
    int nItems = 0;

    if( pInstr == 0 )
        return result;

    // get the instruction item
    const InstructionSetItem* pItem = getInstructionSetItem(pInstr->m_nOpcode);

    // get the opcode
    result += getOpcode(static_cast<InstrOpcode_t>(pInstr->m_nOpcode));
    nItems++;

    // get the modifier if any
    if( pItem->isModifiable() ) {
        result += std::string(".");
        result += getModifier(pInstr->m_nModifier);
        nItems++;
    }

    // check for no parameters instructions
    if( nItems >= pItem->getParamsNumber() )
        return result;
    else
        result += std::string(" ");

    // get the first operand
    result += getADMode(pInstr->m_nAdMode1);
    v1 << pInstr->m_nValue1;
    result += v1.str();
    nItems++;

    // check if we need more
    if( nItems >= pItem->getParamsNumber() )
        return result;
    else
        result += std::string(", ");

    // get the second operand
    result += getADMode(pInstr->m_nAdMode2);
    v2 << pInstr->m_nValue2;
    result += v2.str();

    // return the string
    return result;
}
//}

//{
bool InstructionSet::execute(TaskSet* pTask, Memory* pMemory)
{
    bool isExecuted = false;

    // retrieve the PC & InitAddress of this task
    _uint nInitAddress = pTask->getInitAddress();
    _uint nPC = pTask->getPC();

    // check the memory block
    _uint nBlock = (nInitAddress + nPC) % CORE_MEMORY_SIZE;
    if( (pMemory->getBlock(nBlock)->getStatus()) == Block::BLOCK_EMPTY )
    {
        // too bad, you try to execute an empty block
        pTask->setStatus(TaskSet::TASKSET_KILLED_INVALID_ACCESS);
    }
    else
    {
        // retrieve the instruction opcode
        Instruction* pInstr = pMemory->getBlock(nBlock)->getInstr();
        InstrOpcode_t nOpcode = pInstr->m_nOpcode;

        // create te corresponding instruction
        IInstructionExec* pInstrExec = m_cInstrExecFactory.InstructionExec(nOpcode); 
        
        if( pInstrExec == 0 )
        {
            // opcode unknown
            pTask->setStatus(TaskSet::TASKSET_KILLED_OPCODE_UNKNOWN);
        }
        else
        {
            // execute it
            isExecuted = pInstrExec->execute(pInstr, pTask, pMemory);

            // delete the instruction
            delete pInstrExec;
        }
    }

    return isExecuted;
}
//}
