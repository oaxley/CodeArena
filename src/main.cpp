/**
 * @file    main.cpp
 * @author  Sebastien Legrand
 * @date    2011-11-26
 *
 * @brief   Main entry point
 */

// standard includes
#include <iostream>

// personal includes
#include <oaxlib/oaxlib.h>
#include <oaxlib/version.h>

#include "debug.h"
#include "core.h"
#include "display.h"

// namespace
using namespace std;

/* main function */
int main(int argc, char* argv[])
{
    std::cout << oaxlib::Version::programName() << " - " << oaxlib::Version::versionString() << std::endl;

    if( argc <= 2 ) {
        std::cout << "Syntax: CodeArena <gladiator #1> <gladiator #2>" << std::endl;
        return PROGRAM_INVALID_ARGS_COUNT;
    }

    try
    {
        // create the Core and the associated Display
        Core cCore;
        Display cDisplay(cCore);

        // load gladiators
        cCore.loadGladiator(argv[1]);
        cCore.loadGladiator(argv[2]);

        // gladiators enter in the Arena
        cCore.enterArena( );
        cCore.selectTurnOrder( );

        // set the number max of turn
        cCore.setMaxCoreCycles(CORE_MAX_CYCLES);

        // mainloop
        bool bStart = false;
        Core::CoreStatus_t eGameStatus = Core::CORE_GAME_BEGIN;
        do
        {
            // update the screen
            cDisplay.update( );
            cDisplay.refresh( );

            if( !bStart )
            {
                cDisplay.pause( );
                bStart = true;
            }

            // update the game
            eGameStatus = cCore.update( );
        } while( (eGameStatus != Core::CORE_GAME_OVER) && (eGameStatus != Core::CORE_GAME_END) );

        // display the game final status
        cDisplay.gameOver(eGameStatus);
        cDisplay.pause();

        // display statistics
        cDisplay.quit();
        cCore.printStatistics();

    } catch( std::string& str ) {
        std::cerr << str << std::endl;
    } catch( ... ) {
        std::cerr << "Unhandled exception !" << std::endl;
    }

    return PROGRAM_SUCCESSFULL;
}
