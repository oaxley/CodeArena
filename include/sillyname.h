/**
 * @file	sillyname.h
 * @author	Sebastien Legrand
 * @email	oaxley@gmail.com
 * @date	2011-12-08
 *
 * @brief	Interface / This object returns a silly name taken at random from a list
 */

#ifndef SILLYNAME_H
#define SILLYNAME_H

// standard includes
#include <vector>
#include <string>

// personal includes
#include "types.h"

// class definition
class SillyName
{
    public:     // public methods
        SillyName( );
        virtual ~SillyName( );

        std::string getName( );

    private:    // private methods
        void initialize( );

        // no copy / assignment constructors
        SillyName(const SillyName&);
        SillyName& operator=(const SillyName&);

    private:    // private members
        std::vector< std::pair<std::string, bool> > m_vecNames;
};

#endif // SILLYNAME_H
