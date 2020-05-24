/**
 * @file    taskset.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Interface / Task settings object
 */

#ifndef TASKSET_H
#define TASKSET_H

// standard includes
#include <string>
#include <cstring>

// personal includes
#include "types.h"
#include "instruction.h"

// class definition
class TaskSet
{
    private:        // private members
        std::string     m_strName;          // gladiator name
        _uint           m_eTaskStatus;      // gladiator status
        _uint           m_nInitAddress;     // initial address
        _uint           m_nPC;              // program counter
        _uchar          m_chMarker;         // gladiator marker

        // maintain task flags
        struct FlagRegister_t
        {
            _u8 ZF : 1;         // Zero flag
            _u8 LT : 1;         // Lesser flag
            _u8 EQ : 1;         // Equality flag
            _u8 GT : 1;         // Greater flag

            _u8 : 1;            // reserved for later use
        } m_sFlags;

        // initial gladiator code
        vecInstructionFlow_t m_vInitialCode;

    public:         // public members

        // task status
        enum TaskSetStatus_t
        {
            TASKSET_OUTSIDE = 0,            // gladiator outside the arena
            TASKSET_ALIVE,                  // gladiator alive
            TASKSET_KILLED_INVALID_OPERAND, // invalid operand
            TASKSET_KILLED_INVALID_ACCESS,  // invalid memory access
            TASKSET_KILLED_OPCODE_UNKNOWN,  // try to execute an unknown opcode
            TASKSET_KILLED_DIVIDE_BY_ZERO,  // fatal divide by zero
            TASKSET_KILLED_SUICIDE          // execute a kill opcode
        };

    public:         // public methods
        TaskSet(std::string strName, _uchar chMarker = 'x', _uint nInitAddress = 0);
        virtual ~TaskSet( );

    //{ name set/get
        std::string getName( ) const;
        void setName(std::string strName);
    //}

    //{ status get/set
        _uint getStatus( ) const;
        void setStatus(TaskSetStatus_t nValue);
    //}

    //{ init address set/get
        _uint getInitAddress( ) const;
        void setInitAddress(_uint nInitAddress);
    //}

    //{ PC set/get
        _uint getPC( ) const;
        void setPC(_uint nValue);
    //}

    //{ flags manipulation
        bool getZF( ) const;
        void setZF(bool value);
        bool getLT( ) const;
        void setLT(bool value);
        bool getEQ( ) const;
        void setEQ(bool value);
        bool getGT( ) const;
        void setGT(bool value);
        void clearFlags( );
    //}

    //{ initial code vector manipulation
        vecInstructionFlow_t getInitialCode( );
        void setInitialCode(vecInstructionFlow_t);
        _uint getInstructionsCount( ) const;
    //}

    //{ marker
        _uchar getMarker( ) const;
        void setMarker(_uchar chMarker);
    //}

};

#endif // TASKSET_H
