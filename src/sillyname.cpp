/**
 * @file	sillyname.cpp
 * @author	Sebastien Legrand
 * @email	oaxley@gmail.com
 * @date	2011-12-08
 *
 * @brief	Implementation / This object returns a silly name taken at random from a list
 */

// standard includes
#include <sstream>
#include <cstdlib>
#include <ctime>

// personal includes
#include "sillyname.h"
#include "debug.h"

//{ private methods
// initialize the vector array with silly name
void SillyName::initialize( )
{
    DEBUG_ENTER_METHOD
    // the boolean value is used to indicate if this name is already taken or not
    m_vecNames.push_back( std::pair<std::string, bool>("The Lamer",         false) );
    m_vecNames.push_back( std::pair<std::string, bool>("Al Kaholic",        false) );
    m_vecNames.push_back( std::pair<std::string, bool>("Artie Choke",       false) );
    m_vecNames.push_back( std::pair<std::string, bool>("Toby Continued",    false) );
    m_vecNames.push_back( std::pair<std::string, bool>("Sid Down",          false) );
    m_vecNames.push_back( std::pair<std::string, bool>("Kernel Panic",      false) );
}
//}

// constructor
 SillyName::SillyName( )
{
    DEBUG_ENTER_METHOD
    // initialize the vector
    initialize( );

    // initialize the random generator
    srand(time(NULL));
}

// destructor
/*virtual*/ SillyName::~SillyName( )
{
    DEBUG_ENTER_METHOD
}

// return a name
std::string SillyName::getName( )
{
    DEBUG_ENTER_METHOD
    bool isFound = false;
    _uint nNames = m_vecNames.size();

    // choose a random value
    _uint nValue = rand() % nNames;

    // check if the name is free
    if( m_vecNames[nValue].second == false )
    {
        // mark it as used
        m_vecNames[nValue].second = true;
    }
    else    // not free, find a new one
    {
        // start with the next value
        _uint next = (nValue + 1) % nNames;
        bool isFound = false;
        bool isDone  = false;
        while( !isDone )
        {
            if( m_vecNames[next].second == false )
            {
                isDone = true;
                isFound = true;
            }
            else
            {
                // take the next value
                next = (next + 1) % nNames;

                // we have check them all
                if( next == nValue )
                    isDone = true;
            }
        }

        // we found a new value
        if( isFound )
            nValue = next;
        else
        {
            // create a new name dynamically based on existing names and by adding a random number
            nValue = rand() % nNames;

            std::ostringstream oss;
            _uint nNum   = rand() % 256;        // limit the generated number to [0..255]
            oss << nNum;

            std::string str = m_vecNames[nValue].first + std::string("-") + oss.str();

            // add the name into the array
            m_vecNames.push_back(std::pair<std::string, bool>(str,true));
            nValue = m_vecNames.size() - 1;
        }
    }

    // mark the name as used and return its value
    m_vecNames[nValue].second = true;
    return m_vecNames[nValue].first;
}

