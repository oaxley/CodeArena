/**
 * @file    instructionexecfactory.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-16
 *
 * @brief   Implementation / Instruction exec factory to select the right object to execute at runtime
 */

// standard includes

// personal includes
#include "instructionexecfactory.h"

#include "instrexec/instructionexecmove.h"

#include "instrexec/instructionexecjmp.h"
#include "instrexec/instructionexecjz.h"
#include "instrexec/instructionexecjnz.h"
#include "instrexec/instructionexecjg.h"
#include "instrexec/instructionexecjng.h"
#include "instrexec/instructionexecje.h"
#include "instrexec/instructionexecjne.h"
#include "instrexec/instructionexecjl.h"
#include "instrexec/instructionexecjnl.h"

#include "instrexec/instructionexeccmp.h"
#include "instrexec/instructionexecadd.h"
#include "instrexec/instructionexecsub.h"
#include "instrexec/instructionexecmul.h"
#include "instrexec/instructionexecdiv.h"

#include "instrexec/instructionexecand.h"
#include "instrexec/instructionexecor.h"
#include "instrexec/instructionexecxor.h"

#include "instrexec/instructionexecnop.h"
#include "instrexec/instructionexeckill.h"

#include "debug.h"

// return the right element
IInstructionExec* InstructionExecFactory::InstructionExec(InstrOpcode_t nOpcode)
{
    DEBUG_ENTER_METHOD
    IInstructionExec* pInstrExec = 0;

    switch(nOpcode)
    {
        case OP_MOVE:
            pInstrExec = new InstructionExecMove();
            break;

        case OP_JMP:
            pInstrExec = new InstructionExecJmp();
            break;
        case OP_JZ:
            pInstrExec = new InstructionExecJz();
            break;
        case OP_JNZ:
            pInstrExec = new InstructionExecJnz();
            break;
        case OP_JG:
            pInstrExec = new InstructionExecJg();
            break;
        case OP_JNG:
            pInstrExec = new InstructionExecJng();
            break;
        case OP_JE:
            pInstrExec = new InstructionExecJe();
            break;
        case OP_JNE:
            pInstrExec = new InstructionExecJne();
            break;
        case OP_JL:
            pInstrExec = new InstructionExecJl();
            break;
        case OP_JNL:
            pInstrExec = new InstructionExecJnl();
            break;

        case OP_CMP:
            pInstrExec = new InstructionExecCmp();
            break;
        case OP_ADD:
            pInstrExec = new InstructionExecAdd();
            break;
        case OP_SUB:
            pInstrExec = new InstructionExecSub();
            break;
        case OP_MUL:
            pInstrExec = new InstructionExecMul();
            break;
        case OP_DIV:
            pInstrExec = new InstructionExecDiv();
            break;

        case OP_AND:
            pInstrExec = new InstructionExecAnd();
            break;
        case OP_OR:
            pInstrExec = new InstructionExecOr();
            break;
        case OP_XOR:
            pInstrExec = new InstructionExecXor();
            break;
        case OP_NOT:
            break;

        case OP_NOP:
            pInstrExec = new InstructionExecNop();
            break;
        case OP_KILL:
            pInstrExec = new InstructionExecKill();
            break;
    }

    return pInstrExec;
}
