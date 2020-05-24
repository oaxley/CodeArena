/**
 * @file    display.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-12
 *
 * @brief   Interface / Display the Arena with NCurses library
 */

#ifndef DISPLAY_H
#define DISPLAY_H

// standard includes
#include <ncurses.h>
#include <map>

// personal includes
#include "settings.h"
#include "types.h"
#include "core.h"

// class definition
class Display
{
    private:        // private members

        const Core&     m_rcCore;           // keep a const reference to the Core
        bool            m_NCurseMode;       // true if we are in NCurses mode

        WINDOW*         m_pMainBoard;       // main board window
        WINDOW*         m_pMemoryZone;      // memory zone
        WINDOW*         m_pZone1;           // Gladiator #1 zone
        WINDOW*         m_pZone2;           // Gladiator #2 zone

        std::map<_uchar,_uint> m_mapStats;  // memory occupation statistics

    private:        // private methods

        void initialize( );             // initialize the NCurses library

        void createBoard( );            // create the mainboard
        void createMemory( );           // create the memory zone
        void createZone1( );            // create the Gladiator #1 zone
        void createZone2( );            // create the Gladiator #2 zone
        void createWidgets( );          // create all remaining widgets

        // updates
        void updateBoard( );
        void updateMemory( );
        void updateZone1( );
        void updateZone2( );
        void updateWidgets( );

    public:         // public methods

        Display(const Core&);           // constructor
        virtual ~Display( );            // destructor

        void update( );                 // update the windows
        void refresh( );                // refresh the screen

        int getStats(_uchar marker);    // return the memory statistics

        void pause( );                  // wait for user input
        void quit( );                   // quit NCurses mode

        void gameOver(Core::CoreStatus_t eGameStatus);               // display the gameover window
};
#endif // DISPLAY_H
