/**
 * @file    display.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-12
 *
 * @brief   Implementation / Display the Arena with NCurses library
 */

// standard includes
#include <string>
#include <sstream>

// personal includes
#include <oaxlib/oaxlib.h>
#include <oaxlib/version.h>
#include "display.h"
#include "taskset.h"
#include "debug.h"

//{ private methods
void Display::initialize( )
{
    DEBUG_ENTER_METHOD

    // initialize NCurses
    initscr( );
    start_color( );

    // initialize colors
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_WHITE, COLOR_RED);

    // other NCurses parameters
    raw();                      // line buffering disable
    keypad(stdscr, TRUE);       // retrieve Fn keys
    noecho();                   // do not echo during getch()
    cbreak();                   // no line buffering

    curs_set(0);                // no cursor

    ::refresh();                // be careful not to call the Display::refresh()

    // check the screen size against our required dimensions
    int nRows,nCols;
    getmaxyx(stdscr,nRows,nCols);
    if( (nRows < SCREEN_MAX_Y) || (nCols < SCREEN_MAX_X) ) {
        endwin();

        std::ostringstream v1,v2;
        std::string msg("Error: Your current terminal size is ");
        v1 << nCols;
        v2 << nRows;
        msg = msg + v1.str() + "x" + v2.str();
        msg = msg + std::string(" and should be ");
        v1.seekp(0); v1 << SCREEN_MAX_X;
        v2.seekp(0); v2 << SCREEN_MAX_Y;
        msg = msg + v1.str() + "x" + v2.str();

        throw msg;
    }

    // create the layout
    createBoard( );
    createMemory( );
    createZone1( );
    createZone2( );
    createWidgets( );
}

void Display::createBoard( )
{
    DEBUG_ENTER_METHOD

    // create a new window
    m_pMainBoard = newwin(MAINBOARD_MAX_Y, MAINBOARD_MAX_X, 0, 0);

    // draw a box around
    box(m_pMainBoard, 0, 0);

    // draw the horizontal line
    mvwhline(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, 1, 0, MAINBOARD_MAX_X-2);
    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, 0, ACS_LTEE);
    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_MAX_X-1, ACS_RTEE);

    // draw the 1st vertical line
    mvwvline(m_pMainBoard, MEMORY_ZONE_MAX_Y+2, MAINBOARD_VLINE_1, 0, 8);
    //mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_VLINE_1, ACS_TTEE);
    mvwaddch(m_pMainBoard, MAINBOARD_MAX_Y-1,   MAINBOARD_VLINE_1, ACS_BTEE);

    // draw the 2nd vertical line
    mvwvline(m_pMainBoard, MEMORY_ZONE_MAX_Y+2, MAINBOARD_VLINE_2, 0, 8);
    //mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_VLINE_2, ACS_TTEE);
    mvwaddch(m_pMainBoard, MAINBOARD_MAX_Y-1,   MAINBOARD_VLINE_2, ACS_BTEE);
}

void Display::createMemory( )
{
    DEBUG_ENTER_METHOD
    // create the window
    m_pMemoryZone = newwin(MEMORY_ZONE_MAX_Y, MEMORY_ZONE_MAX_X, 1, 1);
    //wbkgd(m_pMemoryZone,COLOR_PAIR(1));
}

void Display::createZone1( )
{
    DEBUG_ENTER_METHOD
    // create the window
    m_pZone1 = newwin(GLADIATOR_ONE_MAX_Y, GLADIATOR_ONE_MAX_X, MEMORY_ZONE_MAX_Y+2, 1);
}

void Display::createZone2( )
{
    DEBUG_ENTER_METHOD
    // create the window
    m_pZone2 = newwin(GLADIATOR_TWO_MAX_Y, GLADIATOR_TWO_MAX_X, MEMORY_ZONE_MAX_Y+2, MAINBOARD_VLINE_2+1);
}

void Display::createWidgets( )
{
    DEBUG_ENTER_METHOD
//{ title widget
    // create the title
    std::string title(" ");
    title += std::string(oaxlib::Version::programName());
    title += std::string(" - ");
    title += std::string(oaxlib::Version::versionString());
    title += " ";

    // compute the right place
    int nLen = title.size( );
    int nPosX = ((MAINBOARD_MAX_X / 3) - nLen) / 2;
    wmove(m_pMainBoard, 0, nPosX);
    mvwprintw(m_pMainBoard, 0, nPosX, title.c_str( ));

    // add decoration
    mvwaddch(m_pMainBoard, 0, nPosX-1, ACS_RTEE);
    mvwaddch(m_pMainBoard, 0, nPosX+nLen, ACS_LTEE);
//}

//{ occupation zone
    mvwprintw(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_VLINE_1-9, "                    ");
    mvwaddch(m_pMainBoard,  MEMORY_ZONE_MAX_Y+1, MAINBOARD_VLINE_1-10, ACS_RTEE);
    mvwaddch(m_pMainBoard,  MEMORY_ZONE_MAX_Y+1, MAINBOARD_VLINE_2+10, ACS_LTEE);
//}

//{ markers
    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_MAX_X-10, ']');
    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_MAX_X-12, '[');

    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, 9,  '[');
    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, 11, ']');
//}

//{ Core cycles
    nLen = 8;       // 6 char max
    nPosX = (2*(MAINBOARD_MAX_X / 3)) + ((MAINBOARD_MAX_X / 3) - nLen) / 2;
    mvwprintw(m_pMainBoard, 0, nPosX, "        ");
    mvwaddch(m_pMainBoard,  0, nPosX-1, ACS_RTEE);
    mvwaddch(m_pMainBoard,  0, nPosX+8, ACS_LTEE);
//}

}

void Display::updateBoard( )
{
    DEBUG_ENTER_METHOD
}

void Display::updateMemory( )
{
    DEBUG_ENTER_METHOD

    wclear(m_pMemoryZone);

    // reset statistics
    std::map<_uchar,_uint>::iterator it;
    for(it=m_mapStats.begin();it!=m_mapStats.end();it++) {
        (*it).second = 0;
    }

    // parse the memory to draw it
    for(int y=0; y<MEMORY_ZONE_MAX_Y; y++)
    {
        for(int x=0; x<MEMORY_ZONE_MAX_X; x++)
        {
            int nUnit = (y*MEMORY_ZONE_MAX_X) + x;
            Block* pBlock = m_rcCore.m_pMemory->getBlock(nUnit);
            if( pBlock->getStatus( ) != Block::BLOCK_EMPTY )
            {
                _uchar chMarker = (pBlock->getTaskSet())->getMarker();
                mvwaddch(m_pMemoryZone, y, x, chMarker);

                // keep statistics
                m_mapStats[chMarker]++;
            }
        }
    }
}

void Display::updateZone1( )
{
    DEBUG_ENTER_METHOD

    wclear(m_pZone1);

//{ gladiator name
    std::string name = std::string("--=[ ") + (m_rcCore.m_vecTaskSet[0])->getName() + std::string(" ]=--");
    int nLen = name.size();
    int nPosX = (GLADIATOR_ONE_MAX_X - nLen) / 2;
    mvwprintw(m_pZone1, 0, nPosX, name.c_str());
//}

    _uchar chMarker = (m_rcCore.m_vecTaskSet[0])->getMarker();
    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, 10, chMarker);

//{ flags status
    if( (m_rcCore.m_vecTaskSet[0])->getZF() )
    {
        wattron(m_pZone1,A_BOLD);
        mvwaddch(m_pZone1,2,1,'Z');
        wattroff(m_pZone1,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone1,2,1,'Z');
    }

    if( (m_rcCore.m_vecTaskSet[0])->getLT() )
    {
        wattron(m_pZone1,A_BOLD);
        mvwaddch(m_pZone1,3,1,'L');
        wattroff(m_pZone1,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone1,3,1,'L');
    }

    if( (m_rcCore.m_vecTaskSet[0])->getEQ() )
    {
        wattron(m_pZone1,A_BOLD);
        mvwaddch(m_pZone1,4,1,'E');
        wattroff(m_pZone1,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone1,4,1,'E');
    }

    if( (m_rcCore.m_vecTaskSet[0])->getGT() )
    {
        wattron(m_pZone1,A_BOLD);
        mvwaddch(m_pZone1,5,1,'G');
        wattroff(m_pZone1,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone1,5,1,'G');
    }
//}

//{ source code
    _uint nPC = (m_rcCore.m_vecTaskSet[0])->getPC();
    _uint nInitAddress = (m_rcCore.m_vecTaskSet[0])->getInitAddress();

    // we publish 5 instructions if possible
    // 2 before and 2 after
    for(int i=-2;i<3;i++) {
        // retrieve the instruction in the block
        _uint nBlock = (nInitAddress + nPC + i) % CORE_MEMORY_SIZE;
        Instruction* pInstr = (m_rcCore.m_pMemory)->getBlock(nBlock)->getInstr();

        // disassemble the instruction
        std::string strTxtCode = (m_rcCore.m_pInstructionSet)->disassemble(pInstr);

        // add some padding
        int nLen = 30 - strTxtCode.size();
        strTxtCode = std::string(" ") + strTxtCode + std::string(nLen,' ');

        // print the PC value
        mvwprintw(m_pZone1, 4+i, 4, "%+00005d", nPC + i);
        if( i == 0 )
            wattron(m_pZone1, A_REVERSE);

        mvwprintw(m_pZone1, 4+i, 10, strTxtCode.c_str());

        if( i == 0 )
            wattroff(m_pZone1, A_REVERSE);
    }
//}
}

void Display::updateZone2( )
{
    DEBUG_ENTER_METHOD

    wclear(m_pZone2);

//{ gladiator name
    std::string name = std::string("--=[ ") + (m_rcCore.m_vecTaskSet[1])->getName() + std::string(" ]=--");
    int nLen = name.size();
    int nPosX = (GLADIATOR_TWO_MAX_X - nLen) / 2;
    mvwprintw(m_pZone2, 0, nPosX, name.c_str());
//}

    _uchar chMarker = (m_rcCore.m_vecTaskSet[1])->getMarker();
    mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_MAX_X-11, chMarker);


//{ flags status
    if( (m_rcCore.m_vecTaskSet[1])->getZF() )
    {
        wattron(m_pZone2,A_BOLD);
        mvwaddch(m_pZone2,2,GLADIATOR_TWO_MAX_X-2,'Z');
        wattroff(m_pZone2,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone2,2,GLADIATOR_TWO_MAX_X-2,'Z');
    }

    if( (m_rcCore.m_vecTaskSet[1])->getLT() )
    {
        wattron(m_pZone2,A_BOLD);
        mvwaddch(m_pZone2,3,GLADIATOR_TWO_MAX_X-2,'L');
        wattroff(m_pZone2,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone2,3,GLADIATOR_TWO_MAX_X-2,'L');
    }

    if( (m_rcCore.m_vecTaskSet[1])->getEQ() )
    {
        wattron(m_pZone2,A_BOLD);
        mvwaddch(m_pZone2,4,GLADIATOR_TWO_MAX_X-2,'E');
        wattroff(m_pZone2,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone2,4,GLADIATOR_TWO_MAX_X-2,'E');
    }

    if( (m_rcCore.m_vecTaskSet[1])->getGT() )
    {
        wattron(m_pZone2,A_BOLD);
        mvwaddch(m_pZone2,5,GLADIATOR_TWO_MAX_X-2,'G');
        wattroff(m_pZone2,A_BOLD);
    }
    else
    {
        mvwaddch(m_pZone2,5,GLADIATOR_TWO_MAX_X-2,'G');
    }
//}

//{ source code
    _uint nPC = (m_rcCore.m_vecTaskSet[1])->getPC();
    _uint nInitAddress = (m_rcCore.m_vecTaskSet[1])->getInitAddress();

    // we publish 5 instructions if possible
    // 2 before and 2 after
    for(int i=-2;i<3;i++) {
        // retrieve the instruction in the block
        _uint nBlock = (nInitAddress + nPC + i) % CORE_MEMORY_SIZE;
        Instruction* pInstr = (m_rcCore.m_pMemory)->getBlock(nBlock)->getInstr();

        // disassemble the instruction
        std::string strTxtCode = (m_rcCore.m_pInstructionSet)->disassemble(pInstr);

        // add some padding
        int nLen = 30 - strTxtCode.size();
        strTxtCode = std::string(" ") + strTxtCode + std::string(nLen,' ');

        // print the PC value
        mvwprintw(m_pZone2, 4+i, 1, "%+00005d", nPC + i);
        if( i == 0 )
            wattron(m_pZone2, A_REVERSE);

        mvwprintw(m_pZone2, 4+i, 7, strTxtCode.c_str());

        if( i == 0 )
            wattroff(m_pZone2, A_REVERSE);
    }
//}
}

void Display::updateWidgets( )
{
    DEBUG_ENTER_METHOD
//{ Core cycles
    {
        int nLen = 8;
        int nPosX = (2*(MAINBOARD_MAX_X / 3)) + ((MAINBOARD_MAX_X / 3) - nLen) / 2;

        // take care of an infinite value
        if( m_rcCore.m_nMaxCyclesCount == -1 )
            mvwprintw(m_pMainBoard, 0, nPosX, "     oo");
        else
            mvwprintw(m_pMainBoard, 0, nPosX, " %6d",m_rcCore.m_nCyclesCount);
    }
//}

//{ Occupation percentage
    {
        // gladiator one
        _uint nGOnePercent = (10*m_mapStats[(m_rcCore.m_vecTaskSet[0])->getMarker()]) / CORE_MEMORY_SIZE;
        for(int i=0;i<nGOnePercent;i++) {
            mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_VLINE_1-9 + (10-nGOnePercent) + i, '*');
        }

        // gladiator two
        _uint nGTwoPercent = (10*m_mapStats[(m_rcCore.m_vecTaskSet[1])->getMarker()]) / CORE_MEMORY_SIZE;
        for(int i=0;i<nGTwoPercent;i++) {
            mvwaddch(m_pMainBoard, MEMORY_ZONE_MAX_Y+1, MAINBOARD_VLINE_2 + i, '+');
        }

    }
//}
}

//}



//{ xtors
 Display::Display(const Core& cCore) :
     m_rcCore(cCore), m_NCurseMode(false)
{
    DEBUG_ENTER_METHOD
    // initialize NCurses library
    initialize( );
    m_NCurseMode = true;
}

/*virtual*/ Display::~Display( )
{
    DEBUG_ENTER_METHOD
    // release NCurses library
    if( m_NCurseMode )
        ::endwin();
}
//}

void Display::quit( )
{
    ::endwin();
    m_NCurseMode = false;
}

// update the windows
void Display::update( )
{
    DEBUG_ENTER_METHOD
    updateBoard( );
    updateMemory( );
    updateZone1( );
    updateZone2( );
    updateWidgets( );
}

// refresh the screen
void Display::refresh( )
{
    DEBUG_ENTER_METHOD
    // stack all modifications to the back buffer
    wnoutrefresh(m_pMainBoard);
    wnoutrefresh(m_pMemoryZone);
    wnoutrefresh(m_pZone1);
    wnoutrefresh(m_pZone2);

    // update the screen at last
    doupdate();
}

// display the gameover window
void Display::gameOver(Core::CoreStatus_t eGameStatus )
{
    DEBUG_ENTER_METHOD

    // compute the screen center for this window
    int nMaxX = MAINBOARD_MAX_X-20, nMaxY = 7;

    int nX = (MAINBOARD_MAX_X - nMaxX) / 2;
    int nY = (MAINBOARD_MAX_Y - nMaxY) / 2;
    
    // create a new window with a border around
    WINDOW* pWin = newwin(nMaxY, nMaxX, nY, nX);
    box(pWin, 0, 0);

    // add a title depending on the game final status
    std::string title;
    if( eGameStatus == Core::CORE_GAME_END )
        title = std::string(" DRAW GAME ");
    else
        title = std::string(" GAME OVER ");

    // add the title and some decoration
    int nPosX = (nMaxX - title.size()) / 2;
    mvwprintw(pWin, 0, nPosX, title.c_str());
    mvwaddch(pWin, 0, nPosX-1, ACS_RTEE);
    mvwaddch(pWin, 0, nPosX+title.size(), ACS_LTEE);

    // add the result 
    if( eGameStatus == Core::CORE_GAME_END )
    {
        // DRAW GAME
        mvwprintw(pWin, 2, 2, "Both of you have runned for %d cycles but failed to win!",m_rcCore.m_nCyclesCount);
        mvwprintw(pWin, 4, 2, "Go back improve yourself before dare coming back here!");
    }
    else
    {
        // GAME OVER
        TaskSet *winner(0), *loser(0);

        // check who is the winner / loser
        if( m_rcCore.m_vecTaskSet[0]->getStatus() == TaskSet::TASKSET_ALIVE )
        {
            winner = m_rcCore.m_vecTaskSet[0];
            loser  = m_rcCore.m_vecTaskSet[1];
        }
        else
        {
            winner = m_rcCore.m_vecTaskSet[1];
            loser  = m_rcCore.m_vecTaskSet[0];
        }

        mvwprintw(pWin, 2, 2, "'%s' has won the match over '%s' !",(winner->getName()).c_str(),(loser->getName()).c_str());
        std::string result("'");
        result += loser->getName();
        result += std::string("' has lost the game because ");
        switch(loser->getStatus())
        {
            case TaskSet::TASKSET_KILLED_DIVIDE_BY_ZERO:
                result += std::string("he executed an operation that divide by zero");
                break;
            case TaskSet::TASKSET_KILLED_INVALID_ACCESS:
                result += std::string("he did an invalid memory access");
                break;
            case TaskSet::TASKSET_KILLED_OPCODE_UNKNOWN:
                result += std::string("he tried to execute an unknown opcode");
                break;
            case TaskSet::TASKSET_KILLED_SUICIDE:
                result += std::string("he suicided himself with the KILL opcode");
                break;
            case TaskSet::TASKSET_KILLED_INVALID_OPERAND:
                result += std::string("he did an unauthorized operation on an operand");
                break;
        }

        result += std::string(" !!!");
        mvwprintw(pWin, 4, 2, result.c_str());
    }

    // refresh screen
    wrefresh(pWin);
}

// wait for user input
void Display::pause( )
{
    DEBUG_ENTER_METHOD
    ::getch();
}
