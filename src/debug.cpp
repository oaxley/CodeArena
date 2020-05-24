/**
 * @file    debug.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-02-09
 *
 * @brief   Implementation / Debug macros framework
 *
 */

// framework is active only during debug
#ifdef ENABLE_DEBUG

// personal includes
#include "debug.h"

// static variable initialization
unsigned long Debug::m_nIndentation = 0;


//{ private methods

void Debug::printIndentation( )
{
    for(unsigned long nValue=0;nValue < m_nIndentation;nValue++) {
        std::cerr << "  ";
    }
}

//}

//{ xtors

// constructor
 Debug::Debug(const void* object, const char* szFunctionName) :
    m_pObject(object), m_pszFunctionName(0L), m_isIndent(true)
{
    // allocate enough memory for the function name
    int nLen = strlen(szFunctionName);
    m_pszFunctionName=new char[nLen+1];

    // initialize the memory and copy the name
    memset(m_pszFunctionName,0,nLen+1);
    memcpy(m_pszFunctionName,szFunctionName,nLen);

    // create indentation and print the object name/function
    printIndentation();
    std::cerr << "-> [" << m_pObject << "] " << m_pszFunctionName << std::endl;

    // increase indentation
    m_nIndentation++;
}

// destructor
/*virtual*/ Debug::~Debug( )
{
    // reduce indentation
    m_nIndentation--;

    // print indentation followed by object/function name
    printIndentation();
    std::cerr << "<- [" << m_pObject << "] " << m_pszFunctionName << std::endl;

    // release memory
    delete[] m_pszFunctionName;
}

//}

// assert the content of a variable
void Debug::assert(bool value, const char* szFile, int nLine)
{
    if( value == false )
    {
        printIndentation( );
        std::cerr << "** [" << m_pObject << "] Assertion failed on line #" << nLine << " in file [" << szFile << "]" << std::endl;
    }
}

// log a line
void Debug::log(std::string str, bool isCR)
{
    if( m_isIndent )
        printIndentation( );
    std::cerr << str;
    if( isCR )
        std::cerr << std::endl;
    
    m_isIndent = isCR;
}

void Debug::log(const char* szString, bool isCR)
{
    if( m_isIndent )
        printIndentation( );
    
    std::cerr << szString;
    if( isCR ) 
        std::cerr << std::endl;

    m_isIndent = isCR;
}

void Debug::log(void *ptr, bool isCR)
{
    if( m_isIndent )
        printIndentation( );
    
    std::cerr << ptr;
    if( isCR ) 
        std::cerr << std::endl;

    m_isIndent = isCR;
}


#endif
