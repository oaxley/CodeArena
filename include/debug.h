/**
 * @file    debug.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-02-09
 *
 * @brief   Interface / Debug macros framework
 *
 */

// framework is active only during debug
#ifdef ENABLE_DEBUG
//{

// guard
#ifndef DEBUG_H
#define DEBUG_H

// standard includes
#include <iostream>
#include <stdarg.h>
#include <string.h>

// class definition
class Debug
{
    public:     // public methods
        // xtors
        Debug(const void* object, const char* szFunctionName);
        virtual ~Debug( );

        // assertion
        void assert(bool value, const char* szFile, int nLine);
        
        // log a line
        void log(std::string str, bool isCR = true);
        void log(const char* szString, bool isCR = true);
        void log(void *ptr, bool isCR = true);

    private:    // private methods
        void printIndentation( );   // print correct indentation
        
        // no copy / assignation
        Debug(const Debug&);
        Debug& operator=(const Debug&);

    private:    // private members
        static unsigned long    m_nIndentation;
        char*                   m_pszFunctionName;
        const void*             m_pObject;
        bool                    m_isIndent;
};


// macros
#define DEBUG_ENTER_METHOD Debug myDebug(this,__PRETTY_FUNCTION__);
#define DEBUG_ASSERT(expr) myDebug.assert(expr,__FILE__,__LINE__);
#define DEBUG_PRINT(string) myDebug.log(string);
#define DEBUG_WRITE(string) myDebug.log(string, false);

#endif // DEBUG_H (guard)
//}
#else
//{
    #define DEBUG_ENTER_METHOD
    #define DEBUG_ASSERT(expr)
    #define DEBUG_PRINT(string)
    #define DEBUG_WRITE(string)
//}
#endif
