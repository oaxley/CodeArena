/**
 * @file    memory.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-27
 *
 * @brief   Interface / Memory unit
 */

#ifndef MEMORY_H
#define MEMORY_H

// standard includes
#include <vector>

// personal includes
#include "types.h"
#include "block.h"

// class definition
class Memory
{
    private:        // private members

        typedef std::vector< Block* > vecBlock_t;
        vecBlock_t m_vBlocks;       // memory is composed with a list of blocks

        _uint m_nMemorySize;

    public:         // public methods

        Memory(_uint nBlocks);
        virtual ~Memory( );

        Block* getBlock(_uint nUnit);
        void setBlock(_uint nUnit, Block* pBlock);

#ifdef DEBUG
        void dump();
#endif
};


#endif // MEMORY_H
