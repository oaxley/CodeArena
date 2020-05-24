/**
 * @file	marker.cpp
 * @author	Sebastien Legrand
 * @email	oaxley@gmail.com
 * @date	2011-12-14
 *
 * @brief	Implementation / This object returns a marker taken at random from a list
 */

// standard includes
#include <cstdlib>
#include <ctime>

// personal includes
#include "debug.h"
#include "marker.h"

//{ private methods
void Marker::initialize( )
{
    DEBUG_ENTER_METHOD

    // create markers dynamically
    for(_uchar i='0'; i <= '9'; i++)
        m_vecMarkers.push_back( std::pair<_uchar,bool>(i,false) );

    for(_uchar i='a'; i <= 'z'; i++)
        m_vecMarkers.push_back( std::pair<_uchar,bool>(i,false) );

    for(_uchar i='A'; i <= 'Z'; i++)
        m_vecMarkers.push_back( std::pair<_uchar,bool>(i,false) );
}
//}

//{ xtors
 Marker::Marker( )
{
    DEBUG_ENTER_METHOD
    initialize( );

    // initialize the random generator
    srand(time(NULL));
}

/*virtual*/Marker::~Marker( )
{
}
//}

_uchar Marker::getMarker( )
{
    DEBUG_ENTER_METHOD
    bool isFound = false;
    _uint nMarkers = m_vecMarkers.size();
    _uint nValue;

    while( !isFound )
    {
        // choose a value at random
        nValue = rand() % nMarkers;

        if( m_vecMarkers[nValue].second == false )
        {
            isFound = true;
        }
    }

    m_vecMarkers[nValue].second = true;
    return m_vecMarkers[nValue].first;
}
