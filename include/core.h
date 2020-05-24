/**
 * @file    core.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-27
 *
 * @brief   Interface / The main "Core" of CodeArena where the game run
 */

#ifndef CORE_H
#define CORE_H

// standard includes
#include <vector>

// personal includes
#include "settings.h"
#include "types.h"
#include "instructionset.h"
#include "parser.h"
#include "taskset.h"
#include "memory.h"
#include "sillyname.h"
#include "marker.h"

// forward definition
class Display;

// class definition
class Core
{
    private:        // private members
        // instruction set
        InstructionSet* m_pInstructionSet;

        // vector to hold the list of "gladiators"
        std::vector<TaskSet*> m_vecTaskSet;

        // hold the gladiator turn order
        std::vector<_uint>    m_vecTurnOrder;

        // Core memory
        Memory* m_pMemory;

        // random name selector
        SillyName m_xNameSelector;
        Marker* m_pcMarker;

        // cycles count since the begining, and max cycles count
        int m_nCyclesCount;
        int m_nMaxCyclesCount;


    public:         // public members

        enum CoreStatus_t
        {
            CORE_GAME_BEGIN = 0,         // the game is about to start
            CORE_GAME_UPDATE_BEGIN,      // the game is updating
            CORE_GAME_UPDATE_END,        // the game has been updated
            CORE_GAME_END,               // all cycles have been consumed
            CORE_GAME_OVER               // the game is terminated because of a killed
        };

    public:         // public methods

        //{ xtors
        Core( );
        virtual ~Core( );
        //}

        // set the number max of cycles (-1: infinite)
        void setMaxCoreCycles(int nCount = CORE_MAX_CYCLES);

        // load a gladiator
        _uint loadGladiator(std::string strFilename);

        // return the name of a previously loaded gladiator
        std::string getGladiatorName(_uint id);

        // put the gladiators in the arena
        void enterArena( );

        // select the turn order
        void selectTurnOrder( );

        // update the core: each gladiator do a turn and update the core
        CoreStatus_t update( );

        // display final statistics
        void printStatistics( );

        // Display class is friend to us
        friend class Display;

#ifdef ENABLE_DEBUG
        void dump( );
#endif
};

#endif // CORE_H
