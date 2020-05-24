/**
 * @file	marker.h
 * @author	Sebastien Legrand
 * @email	oaxley@gmail.com
 * @date	2011-12-14
 *
 * @brief	Interface / This object returns a marker taken at random from a list
 */

#ifndef MARKER_H
#define MARKER_H

// standard includes
#include <vector>

// personal includes
#include "types.h"

// class definition
class Marker
{
    public:     // public methods
        Marker( );
        virtual ~Marker( );

        // return a marker taken at random
        _uchar getMarker( );

    private:    // private methods
        void initialize( );

        // no copy / assignation
        Marker(const Marker&);
        Marker& operator=(const Marker&);

    private:    // private members
        std::vector< std::pair<_uchar,bool> > m_vecMarkers;
};

#endif // MARKER_H
