/**
 * @file    memory.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-27
 *
 * @brief   Interface / Memory unit
 */

// standard includes
#include <iostream>

// personal includes
#include "memory.h"
#include "debug.h"

// constructor
 Memory::Memory(_uint nBlocks) :
    m_nMemorySize(nBlocks)
{
    DEBUG_ENTER_METHOD
    // create the memory blocks
    for(_uint i=0;i<nBlocks;i++) {
        Block* pBlock = new Block();
        m_vBlocks.push_back(pBlock);
    }
}

// destructor
/*virtual*/ Memory::~Memory( )
{
    DEBUG_ENTER_METHOD
    for(_uint i=0;i<m_nMemorySize;i++) {
        delete m_vBlocks[i];
    }
}

// retrieve a block of memory
Block* Memory::getBlock(_uint nUnit)
{
    DEBUG_ENTER_METHOD
    _uint nItem = (nUnit % m_nMemorySize);
    return m_vBlocks[nItem];
}

// set a block of memory
void Memory::setBlock(_uint nUnit, Block* pBlock)
{
    DEBUG_ENTER_METHOD
    _uint nItem = (nUnit % m_nMemorySize);
    delete m_vBlocks[nItem];
    m_vBlocks[nItem] = pBlock;
}

#ifdef DEBUG
// dump memory
void Memory::dump( )
{
    for(_uint i=0;i<m_nMemorySize;i++)
    {
        Block* pBlock = m_vBlocks[i];
        if( pBlock->getStatus() == Block::BLOCK_EMPTY )
            std::cout << ".";
        else
            std::cout << "x";

        if( (i>0) && (i % 170 == 0) )
            std::cout << std::endl;
    }
    std::cout << std::endl;
}
#endif
