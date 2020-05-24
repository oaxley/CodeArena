/**
 * @file    core.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-04
 *
 * @brief   Implementation / The main "Core" of CodeArena where the game run
 */

// standard includes
#include <iostream>
#include <ctime>
#include <cstdlib>

// personal includes
#include "core.h"
#include "block.h"
#include "instruction.h"
#include "debug.h"

//{ xtors

// constructor
 Core::Core( ) :
    m_pInstructionSet(0), m_pMemory(0), m_nCyclesCount(0), m_nMaxCyclesCount(CORE_MAX_CYCLES)
{
    DEBUG_ENTER_METHOD

    // create Instruction set
    m_pInstructionSet = new InstructionSet( );

    // create memory
    m_pMemory = new Memory(CORE_MEMORY_SIZE);

    // initialize the random generator
    srand(time(NULL));

    // create marker
    m_pcMarker = new Marker();
}

// destructor
/*virtual*/ Core::~Core( )
{
    DEBUG_ENTER_METHOD

    // delete InstructionSet
    DEBUG_ASSERT(m_pInstructionSet != 0)
    delete m_pInstructionSet;

    // delete TaskSet vector
    std::vector<TaskSet*>::iterator it = m_vecTaskSet.begin();
    while( it != m_vecTaskSet.end() ) {
        DEBUG_ASSERT(*it != 0)
        delete *(it++);
    }

    // delete memory
    DEBUG_ASSERT(m_pMemory != 0)
    delete m_pMemory;
}

//}

// set the number max of cycles (-1: infinite)
void Core::setMaxCoreCycles(int nCount)
{
    DEBUG_ENTER_METHOD
    m_nMaxCyclesCount = nCount;
}

// load a gladiator
_uint Core::loadGladiator(std::string strFilename)
{
    DEBUG_ENTER_METHOD

    std::pair<_uint,std::string> retval;

    if( m_vecTaskSet.size() >= NB_GLADIATORS )
        throw std::string("Already too many gladiators for this arena !");

    // read the file
    Parser* pParser = new Parser(*m_pInstructionSet);
    retval = pParser->loadFile(strFilename);

    // check the name
    if( retval.second.size() == 0 )
        retval.second = m_xNameSelector.getName( );

    // create the associated taskset
    TaskSet* pTaskset = new TaskSet(retval.second, m_pcMarker->getMarker());
    pTaskset->setInitialCode(pParser->getInstructionFlow());
    m_vecTaskSet.push_back(pTaskset);

    // free memory
    delete pParser;

    // return the number of lines
    return retval.first;
}

// return the name of a previously loaded gladiator
std::string Core::getGladiatorName(_uint id)
{
    DEBUG_ENTER_METHOD
    // be sure the id is in the range
    return m_vecTaskSet[(id%NB_GLADIATORS)]->getName( );
}

// put the gladiators in the arena
void Core::enterArena( )
{
    DEBUG_ENTER_METHOD

    std::vector<TaskSet*>::iterator itOne;
    _uint nMyCodeLen,nMyStartPos;

    // loop through all gladiators
    for(itOne = m_vecTaskSet.begin(); itOne != m_vecTaskSet.end(); itOne++)
    {
        // code length
        nMyCodeLen  = (*itOne)->getInstructionsCount( );

        bool bDone = false;
        while( !bDone )
        {
            // get a random position - by default is a good one
            nMyStartPos = rand() % CORE_MEMORY_SIZE;
            bDone = true;

            // check all memory block to confirm
            _uint nUnit = 0;
            while( nUnit < nMyCodeLen )
            {
                if( (m_pMemory->getBlock(nMyStartPos+nUnit)->getStatus( )) == Block::BLOCK_USED )
                {
                    bDone = false;
                    break;
                }

                // next block
                nUnit = (nUnit + 1) % CORE_MEMORY_SIZE;
            }
        }

        // mark the position as valid
        (*itOne)->setInitAddress(nMyStartPos);

        // fill the memory with the gladiator code
        _uint nUnit = nMyStartPos;
        vecInstructionFlow_t   initCode = (*itOne)->getInitialCode( );
        vecInstructionFlowIt_t itTwo = initCode.begin();
        while( itTwo != initCode.end() )
        {
            // retrieve the corresponding block
            Block* pBlock = m_pMemory->getBlock(nUnit++);

            // set the instruction and the taskset to whom it belongs
            pBlock->setInstr(*itTwo);
            pBlock->setTaskSet(*itOne);
            pBlock->setStatus(Block::BLOCK_USED);

            // next instruction
            itTwo++;
        }

        // gladiator is in!
        (*itOne)->setStatus(TaskSet::TASKSET_ALIVE);

    } // for
}

// select the turn order
void Core::selectTurnOrder( )
{
    DEBUG_ENTER_METHOD

    _uint nGladiators = m_vecTaskSet.size();
    _uint* pTracker = 0;                          // keep track of already assigned gladiator

    // create the tracker array
    pTracker = new _uint[nGladiators];
    memset(pTracker, 0, sizeof(_uint)*nGladiators);

    _uint count = 0;
    while( count < nGladiators-1 )
    {
        // select a gladiator
        _uint nGladiator = rand() % nGladiators;

        // check if he has already a turn assigned
        if( pTracker[nGladiator] == 1 )
            continue;
        else
        {
            m_vecTurnOrder.push_back(nGladiator);
            pTracker[nGladiator] = 1;
            count++;
        }
    }

    // determine the last gladiator
    for(count = 0; count < nGladiators; count++)
    {
        if( pTracker[count] == 0 )
            m_vecTurnOrder.push_back(count);
    }

    // delete allocated memory
    delete pTracker;
}

// update the core: each gladiator do a turn and update the core
Core::CoreStatus_t Core::update( )
{
    DEBUG_ENTER_METHOD

    // start update
    CoreStatus_t eFinalStatus = CORE_GAME_UPDATE_BEGIN;

    // follow the selected turn order
    std::vector<_uint>::iterator itOne = m_vecTurnOrder.begin();
    while( eFinalStatus == CORE_GAME_UPDATE_BEGIN )
    {
        // execute the instruction
        bool isExecuted = m_pInstructionSet->execute(m_vecTaskSet[*itOne], m_pMemory);

        if( isExecuted )
        {
            // next gladiator
            itOne++;
            if( itOne == m_vecTurnOrder.end() )
                eFinalStatus = CORE_GAME_UPDATE_END;
        }
        else
            eFinalStatus = CORE_GAME_OVER;
    } // while

    // no need to increase the number of cycle if the game is over
    if( eFinalStatus != CORE_GAME_OVER )
    {
        // increase the number of cycles
        m_nCyclesCount = m_nCyclesCount + 1;

        if( m_nCyclesCount >= m_nMaxCyclesCount )
            eFinalStatus = CORE_GAME_END;
    }

    // the game has been updated
    return eFinalStatus;
}

// display final statistics
void Core::printStatistics( )
{
    DEBUG_ENTER_METHOD

    std::cout << "------ Statistics ------" << std::endl;
    //{ 1. territory
    std::cout << std::endl;
    std::cout << "1. Territory" << std::endl;
    
    // compute stats
    std::map<_uchar, _uint> mapStats;
    mapStats[m_vecTaskSet[0]->getMarker()] = 0;
    mapStats[m_vecTaskSet[1]->getMarker()] = 0;
    for(int y=0; y<MEMORY_ZONE_MAX_Y; y++)
    {
        for(int x=0; x<MEMORY_ZONE_MAX_X; x++)
        {
            int nUnit = (y*MEMORY_ZONE_MAX_X) + x;
            Block* pBlock = m_pMemory->getBlock(nUnit);
            if( pBlock->getStatus( ) != Block::BLOCK_EMPTY )
            {
                _uchar chMarker = (pBlock->getTaskSet())->getMarker();
                mapStats[chMarker]++;
            }
        }
    }

    std::cout << "    '" << m_vecTaskSet[0]->getName() << "' : ";
    std::cout << (double)(100.0*mapStats[m_vecTaskSet[0]->getMarker()]) / CORE_MEMORY_SIZE;
    std::cout << " %" << std::endl;
     
    std::cout << "    '" << m_vecTaskSet[1]->getName() << "' : ";
    std::cout << (double)(100.0*mapStats[m_vecTaskSet[1]->getMarker()]) / CORE_MEMORY_SIZE;
    std::cout << " %" << std::endl;
    //}

    //{ 2. cycles runned
    std::cout << std::endl;
    std::cout << "2. Cycles" << std::endl;
    std::cout << "    " << m_nCyclesCount << " cycles runned out of " << m_nMaxCyclesCount;
    std::cout << " (" << (double)(100.0*m_nCyclesCount)/m_nMaxCyclesCount << " %)";
    std::cout << std::endl;
    //}

    //{ 3. code generated
    std::cout << std::endl;
    std::cout << "3. Code generated" << std::endl;
    
    std::cout << "    '" << m_vecTaskSet[0]->getName() << "' : "; 
    
    int init = m_vecTaskSet[0]->getInstructionsCount();
    int final = mapStats[m_vecTaskSet[0]->getMarker()];

    std::cout << "from " << init;
    std::cout << " to " << final;
    std::cout << " (+" << (double)(100.0*(final-init)/init) << " %)";
    std::cout << std::endl;

    std::cout << "    '" << m_vecTaskSet[1]->getName() << "' : ";

    init = m_vecTaskSet[1]->getInstructionsCount();
    final = mapStats[m_vecTaskSet[1]->getMarker()];

    std::cout << "from " << init;
    std::cout << " to " << final;
    std::cout << " (+" << (double)(100.0*(final-init)/init) << " %)";
    std::cout << std::endl;

    std::cout << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << std::endl;
    //}
}

#ifdef ENABLE_DEBUG
void Core::dump( )
{
    std::vector<TaskSet*>::iterator itOne;

    // loop through all glaiators
    for(itOne = m_vecTaskSet.begin(); itOne != m_vecTaskSet.end(); itOne++)
    {
        std::cout << (*itOne)->getName( ) << ":" << std::endl;
        std::cout << "Code length      : " << (_uint)(*itOne)->getInstructionsCount( ) << std::endl;
        std::cout << "Initial Addresse : " << (_uint)(*itOne)->getInitAddress( ) << std::endl;
        std::cout << "Status           : " << (_uint)(*itOne)->getStatus( ) << std::endl;
        std::cout << "PC               : " << (_uint)(*itOne)->getPC( ) << std::endl;
        std::cout << "Flags            : ";

        std::string str = ((*itOne)->getZF()) ? "Z1 |" : "Z0 |";
        std::cout << str;
        str = ((*itOne)->getLT()) ? " L1 |" : " L0 |";
        std::cout << str;
        str = ((*itOne)->getEQ()) ? " E1 |" : " E0 |";
        std::cout << str;
        str = ((*itOne)->getGT()) ? " G1" : " G0";
        std::cout << str;
        std::cout << std::endl;

        // dump assembly code
        std::cout << "Source code:" << std::endl;
        vecInstructionFlow_t vCode = (*itOne)->getInitialCode();
        vecInstructionFlowIt_t itTwo;
        for(itTwo = vCode.begin(); itTwo!=vCode.end();itTwo++)
        {
            std::cout << m_pInstructionSet->disassemble(*itTwo) << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Gladiators turn is as follows:" << std::endl;
    _uint count = 1;
    std::vector<_uint>::iterator itTwo;
    for(itTwo = m_vecTurnOrder.begin(); itTwo != m_vecTurnOrder.end(); itTwo++)
    {
        std::cout << "#" << count << " - Gladiator: " << m_vecTaskSet[(*itTwo)]->getName( ) << std::endl;
        count++;
    }

    std::cout << std::endl;
    std::cout << "Memory disassemble:" << std::endl;

    // disassemble the memory where task are located
    std::vector<TaskSet*>::iterator itThree;

    for(count=0,itThree = m_vecTaskSet.begin(); itThree != m_vecTaskSet.end(); itThree++,count++)
    {
        _uint nInitAddress = (*itThree)->getInitAddress();
        _uint nBytes = (*itThree)->getInstructionsCount();

        std::cout << "Task[" << count << "] - Init@: " << nInitAddress << " - Count: " << nBytes << std::endl;
        for(_uint nBlock=0;nBlock < nBytes;nBlock++)
        {
            // get the instruction in memory
            Block* pBlock = m_pMemory->getBlock(nBlock+nInitAddress);
            Instruction* pInstr = pBlock->getInstr();

            // disassemble it
            std::cout << "Block " << pBlock << " - " << pInstr << " : ";
            std::cout << "(" << (int)pInstr->m_nOpcode << ").(" << (int)pInstr->m_nModifier << ") ";
            std::cout << "(" << (int)pInstr->m_nAdMode1 << ")[" << (int)pInstr->m_nValue1 << "], ";
            std::cout << "(" << (int)pInstr->m_nAdMode2 << ")[" << (int)pInstr->m_nValue2 << "] - ";
            std::cout << m_pInstructionSet->disassemble(pInstr) << std::endl;
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;
}
#endif
