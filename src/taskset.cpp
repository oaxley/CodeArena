/**
 * @file    taskset.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Implementation / Task settings object
 */

// standard includes

// personal includes
#include "debug.h"
#include "taskset.h"

// constructor
 TaskSet::TaskSet(std::string strName, _uchar chMarker, _uint nInitAddress) :
    m_strName(strName), m_eTaskStatus(TASKSET_OUTSIDE), m_nInitAddress(nInitAddress), m_nPC(0), m_chMarker(chMarker)
{
    DEBUG_ENTER_METHOD
    // initialize flag register
    memset(&m_sFlags,0L,sizeof(struct FlagRegister_t));
}

// destructor
/*virtual*/ TaskSet::~TaskSet( )
{
    DEBUG_ENTER_METHOD

    // delete the instruction flow
    DEBUG_PRINT("Initialize iterator")
    vecInstructionFlowIt_t it = m_vInitialCode.begin();
    
    DEBUG_PRINT("Start loop")
    while( it != m_vInitialCode.end() )
    {
        DEBUG_WRITE("Delete instruction ")
        DEBUG_PRINT((void*)*it)
        DEBUG_ASSERT(*it != 0)
        delete *it;

        it++;
    }
}

//{ name set/get
std::string TaskSet::getName( ) const
{
    DEBUG_ENTER_METHOD
    return m_strName;
}

void TaskSet::setName(std::string strName)
{
    DEBUG_ENTER_METHOD
    m_strName = strName;
}
//}

//{ status n
_uint TaskSet::getStatus( ) const
{
    DEBUG_ENTER_METHOD
    return m_eTaskStatus;
}

void TaskSet::setStatus(TaskSetStatus_t eValue)
{
    DEBUG_ENTER_METHOD
    m_eTaskStatus = eValue;
}
//}

//{ init address set/get
_uint TaskSet::getInitAddress( ) const
{
    DEBUG_ENTER_METHOD
    return m_nInitAddress;
}

void TaskSet::setInitAddress(_uint nInitAddress)
{
    DEBUG_ENTER_METHOD
    m_nInitAddress = nInitAddress;
}
//}

//{ PC set/get
_uint TaskSet::getPC( ) const
{
    DEBUG_ENTER_METHOD
    return m_nPC;
}

void TaskSet::setPC(_uint nValue)
{
    DEBUG_ENTER_METHOD
    m_nPC = nValue;
}
//}

//{ flags manipulation
bool TaskSet::getZF( ) const
{
    DEBUG_ENTER_METHOD
    return m_sFlags.ZF;
}
void TaskSet::setZF(bool value)
{
    DEBUG_ENTER_METHOD
    m_sFlags.ZF = value;
}

bool TaskSet::getLT( ) const
{
    DEBUG_ENTER_METHOD
    return m_sFlags.LT;
}
void TaskSet::setLT(bool value)
{
    DEBUG_ENTER_METHOD
    m_sFlags.LT = value;
}

bool TaskSet::getEQ( ) const
{
    DEBUG_ENTER_METHOD
    return m_sFlags.EQ;
}
void TaskSet::setEQ(bool value)
{
    DEBUG_ENTER_METHOD
    m_sFlags.EQ = value;
}

bool TaskSet::getGT( ) const
{
    DEBUG_ENTER_METHOD
    return m_sFlags.GT;
}
void TaskSet::setGT(bool value)
{
    DEBUG_ENTER_METHOD
    m_sFlags.GT = value;
}

void TaskSet::clearFlags( )
{
    m_sFlags.LT = false;
    m_sFlags.EQ = false;
    m_sFlags.GT = false;
}
//}

//{ initial code vector manipulation
vecInstructionFlow_t TaskSet::getInitialCode( )
{
    DEBUG_ENTER_METHOD
    return m_vInitialCode;
}

void TaskSet::setInitialCode(vecInstructionFlow_t vecInitCode)
{
    DEBUG_ENTER_METHOD
    m_vInitialCode = vecInitCode;
}

_uint TaskSet::getInstructionsCount( ) const
{
    DEBUG_ENTER_METHOD
    return m_vInitialCode.size();
}
//}

//{ marker
_uchar TaskSet::getMarker( ) const
{
    DEBUG_ENTER_METHOD
    return m_chMarker;
}

void TaskSet::setMarker(_uchar chMarker)
{
    DEBUG_ENTER_METHOD
    m_chMarker = chMarker;
}

//}
