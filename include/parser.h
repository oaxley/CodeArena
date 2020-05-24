/**
 * @file    parser.h
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-11-26
 *
 * @brief   Interface / Parse the gladiator code and compile it
 */

// standard
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <cstring>

// personal
#include "types.h"
#include "settings.h"
#include "opcode.h"
#include "instruction.h"
#include "instructionset.h"

// class definition
class Parser
{
    private:    // private members
        _uint m_nLineCount;                             // number of lines in the program
        _uint m_nInstructionCount;                      // number of instructions

        std::string m_strTokenDelims;                   // string containing all delimiters (\t,. )

        std::vector<std::string> m_vecTokens;           // list of token after extraction
        std::map<std::string, _uint> m_mapLabels;       // map containing the label and its relative position

        // map for unresolved jumps
        std::map<std::string, std::vector<_uint> > m_mapUnresolvedLabels;

        InstructionSet& m_rISet;                        // reference to the Core instruction set
        vecInstructionFlow_t m_vecInstructionFlow;      // instruction flow

        // parser functions return values (FSM)
        enum ParserResult_t
        {
            PARSER_INVALID_TOKEN = 0,       // to detect error
            PARSER_SYNTAX_ERROR,            // syntax error

            PARSER_PARSE_BEGIN,             // start the parsing
            PARSER_PARSE_END,               // parsing operations for this token is complete

            PARSER_DISCARD_TOKEN,           // discard the token (mainly comments and empty line)
            PARSER_INTERPRETE_TOKEN,        // token is valid and ready to be interpreted
            PARSER_COMPILE_TOKEN            // token is valid and ready to be compiled
        };

        // instruction fields
        enum InstructionFields_t
        {
            INSTR_FIELD_OPCODE = 0,         // opcode
            INSTR_FIELD_MODIFIER,           // modifier
            INSTR_FIELD_ADMODE1,
            INSTR_FIELD_VALUE1,
            INSTR_FIELD_ADMODE2,
            INSTR_FIELD_VALUE2,

            INSTR_FIELD_END
        };

        InstructionFields_t m_nCompilationField;    // field being analyzed during compilation
        _uint m_nFieldIndex;                        // field index used during compilation

    private:    // private methods
        //{ token manipulation
        ParserResult_t readTokens(char* pszBuffer);
        ParserResult_t interpreteTokens( );
        ParserResult_t compileTokens( );
        //}

        //{ compilation
        InstructionFields_t getOpcode(Instruction*);
        InstructionFields_t getModifier(Instruction*);
        InstructionFields_t getAdMode(Instruction*);
        InstructionFields_t getValue(Instruction*);
        //}

        //{ jumps resolution
        void resolveJumps();
        //}

    public:     // public methods
        Parser(InstructionSet& rISet);
        virtual ~Parser();

        // load a file. Return the number of lines read + the gladiator name
        std::pair<_uint, std::string> loadFile(std::string strFilename);

        // string manipulation
        void uppercase(std::string& str);
        bool isAlpha(std::string& str);
        bool isDigit(std::string& str);

        // return the instruction flow
        vecInstructionFlow_t getInstructionFlow( );
};
