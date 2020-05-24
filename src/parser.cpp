/**
 * @file    parser.cpp
 * @author  Sebastien Legrand
 * @email   oaxley@gmail.com
 * @date    2011-12-02
 *
 * @brief   Implementation / Parse the gladiator's source code
 */

// standard includes
#include <iostream>
#include <sstream>
#include <cstring>

// personal includes
#include "parser.h"
#include "debug.h"

// constructor
// need the InstructionSet object
 Parser::Parser( InstructionSet& rISet ) :
    m_nLineCount(0), m_nInstructionCount(0), m_rISet(rISet)
{
    DEBUG_ENTER_METHOD

    // initialize the delimiters
    m_strTokenDelims = rISet.getDelimitersList();

}

// destructor
/*virtual*/ Parser::~Parser( )
{
    DEBUG_ENTER_METHOD

}

// load a source code file
// return the number of lines read and the gladiator name if any
std::pair<_uint,std::string> Parser::loadFile(std::string strFilename)
{
    DEBUG_ENTER_METHOD

    std::ifstream fh;
    std::ostringstream oss;
    std::string strName("");
    char* pszBuffer = 0;

    // open the file
    fh.open(strFilename.c_str(), std::fstream::in);
    if( ! fh.is_open() )
        throw std::string("Unable to open the file!");

    // allocate memory to read lines
    pszBuffer = new char[MAX_CHARS];
    memset(pszBuffer, 0, sizeof(char)*MAX_CHARS);

    // check for the name of the gladiator on the very first line
    fh.getline(pszBuffer, MAX_CHARS);

    // try to locate the marker if it's a comment line
    if( pszBuffer[0] == ';' )
    {
        char* pBegin=0;
        if( (pBegin = strstr(pszBuffer,"-=[")) != NULL )
        {
            pBegin += 3;                    // remove the marker
            char *pEnd = pBegin;

            // find the end marker
            pEnd = strstr(pEnd,"]=-");
            if( pEnd != NULL )
                strName = std::string(pBegin,(int)(pEnd-pBegin));       // copy the name between the markers
        }
    }

    // read the rest of the file
    do
    {
        // take care of the premature EOF
        if( fh.eof() )
            continue;

        // number of char reads
        int count = fh.gcount()-1;
        m_nLineCount++;

        // remove empty line
        if( count == 0 )
            continue;

        // tokens at work!
        ParserResult_t nResult = PARSER_PARSE_BEGIN;
        bool bDone = false;
        while( !bDone )
        {
            switch(nResult)
            {
                case PARSER_PARSE_BEGIN:
                    nResult = readTokens(pszBuffer);
                    break;

                case PARSER_PARSE_END:
                case PARSER_DISCARD_TOKEN:
                    bDone = true;
                    break;

                case PARSER_INTERPRETE_TOKEN:
                    nResult = interpreteTokens();
                    break;

                case PARSER_COMPILE_TOKEN:
                    nResult = compileTokens();
                    m_nInstructionCount++;
                    break;

                case PARSER_SYNTAX_ERROR:
                    oss << m_nLineCount;
                    throw (std::string("Syntax error on line ") + oss.str());
                    break;

                case PARSER_INVALID_TOKEN:
                    oss << m_nLineCount;
                    throw (std::string("Invalid token found on line ") + oss.str());
                    break;
            }
        } // end while

        // read the next line
        memset(pszBuffer, 0, sizeof(char)*MAX_CHARS);
        fh.getline(pszBuffer, MAX_CHARS);

    } while( ! fh.eof() );


    // resolve jumps
    resolveJumps();

    // end
    delete[] pszBuffer;
    fh.close( );

    // return the number of lines processed
    return std::pair<_uint, std::string>(m_nLineCount, strName);
}

// transform a string into a uppercase string (!! not UTF8 compatible)
void Parser::uppercase(std::string& str)
{
    DEBUG_ENTER_METHOD

    const char* pBegin = str.data( );
    const char* pSrc = pBegin;

    char* pBuffer = new char[ str.length( ) ];
    char* pDst = pBuffer;

    while( (unsigned)(pSrc - pBegin) < str.length( ) ) {
        if( (*pSrc >= 'a') && (*pSrc <= 'z') )
            *pDst++ = *pSrc - 32;
        else
            *pDst++ = *pSrc;

        *pSrc++;
    }

    str = std::string((const char*)pBuffer, (unsigned)(pSrc-pBegin));
    delete[] pBuffer;
}

// read a serie of tokens from the buffer
// return the next step to be performed
Parser::ParserResult_t Parser::readTokens(char* pszBuffer)
{
    DEBUG_ENTER_METHOD

    // comments are easy to treat
    if( pszBuffer[0] == ';' )
        return PARSER_DISCARD_TOKEN;

    // split the line
    char* pToken = strtok(pszBuffer, m_strTokenDelims.c_str());
    while( pToken != NULL )
    {
        // store the result in the vector
        std::string str(pToken); uppercase(str);
        m_vecTokens.push_back(str);

        // next token
        pToken = strtok(NULL, m_strTokenDelims.c_str());
    }

    // interprete the token
    return PARSER_INTERPRETE_TOKEN;
}

// compile the tokens actually in the pipe
// return the next step to be performed
Parser::ParserResult_t Parser::compileTokens()
{
    DEBUG_ENTER_METHOD

    Instruction* pInstr = 0;
    m_nCompilationField = INSTR_FIELD_OPCODE;
    m_nFieldIndex = 0;

    // create a new instruction
    pInstr = new Instruction;

    bool bDone = false;
    while (!bDone)
    {
        switch(m_nCompilationField)
        {
            case INSTR_FIELD_OPCODE:
                m_nCompilationField = getOpcode(pInstr);
                m_nFieldIndex++;
                break;

            case INSTR_FIELD_MODIFIER:
                m_nCompilationField = getModifier(pInstr);
                m_nFieldIndex++;
                break;

            case INSTR_FIELD_ADMODE1:
            case INSTR_FIELD_ADMODE2:
                m_nCompilationField = getAdMode(pInstr);
                break;

            case INSTR_FIELD_VALUE1:
            case INSTR_FIELD_VALUE2:
                m_nCompilationField = getValue(pInstr);
                m_nFieldIndex++;
                break;

            case INSTR_FIELD_END:
                bDone = true;
                break;
        }

        if( (m_nFieldIndex >= m_vecTokens.size()) && !bDone )
            bDone = true;
    }

    // add the instruction to the instruction flow
    m_vecInstructionFlow.push_back(pInstr);

    // remove the tokens from the pipe
    m_vecTokens.clear();

    // parsing completed
    return PARSER_PARSE_END;
}

// analyze the token to determine its validity
// return the next step to be performed
Parser::ParserResult_t Parser::interpreteTokens()
{
    DEBUG_ENTER_METHOD

    // get the first token and check its validity
    std::string token = m_vecTokens.front();
    bool isTokenValid = false;

    if (m_rISet.getOpcode(token) != OP_UNKNOWN)
        isTokenValid = true;

    // try to recognize difference between a label and an instruction like NOP
    if( (m_vecTokens.size() == 1) && (!isTokenValid) )
    {
        // insert the current label/instruction count in the map
        m_mapLabels.insert( std::pair<std::string, _uint>(token,m_nInstructionCount));

        // remove the label from the vector
        m_vecTokens.pop_back();

        // no compilation needed
        return PARSER_PARSE_END;
    }

    // check if it exists
    if( !isTokenValid )
        return PARSER_INVALID_TOKEN;

    // check if we get enough tokens
    if( m_vecTokens.size() != (m_rISet.getInstructionSetItem(token))->getParamsNumber() )
        return PARSER_SYNTAX_ERROR;

    // compile the token
    return PARSER_COMPILE_TOKEN;
}

// resolve "forward" jumps: these jumps are defined somewhere after the instruction that
// reference it
void Parser::resolveJumps()
{
    DEBUG_ENTER_METHOD

    std::map<std::string, std::vector<_uint> >::iterator itOne;
    std::map<std::string, _uint>::iterator itTwo;

    // nothing to do if container empty
    if( m_mapUnresolvedLabels.empty() )
        return;

    // take one entry at a time
    for(itOne = m_mapUnresolvedLabels.begin(); itOne != m_mapUnresolvedLabels.end(); itOne++)
    {
        std::vector<_uint> *InstrList = &((*itOne).second);

        // check if the label is defined in the label table
        if( (itTwo=m_mapLabels.find((*itOne).first)) != m_mapLabels.end() )
        {
            std::vector<_uint>::iterator itThree = InstrList->begin();
            while( itThree != InstrList->end() )
            {
                _uint nInstruction = (*itThree);
                Instruction* pInstr = m_vecInstructionFlow[nInstruction];
                pInstr->m_nValue1 = static_cast<_s16>((*itTwo).second);
                itThree++;
            }
        }
        else
        {
            // not found
            std::string msg = std::string("label [") + (*itOne).first + std::string("] is referenced in an instruction but not defined elsewhere!");
            throw msg;
        }
    }
}

// retrieve the token from the pipe and try to determine its real value
Parser::InstructionFields_t Parser::getValue(Instruction* pInstr)
{
    DEBUG_ENTER_METHOD

    // select the right value
    _s16* pValue = (m_nCompilationField == INSTR_FIELD_VALUE1) ? &pInstr->m_nValue1 : &pInstr->m_nValue2;

    // check if it's belonging to the labels
    std::map<std::string, _uint>::iterator it;
    it = m_mapLabels.find(m_vecTokens[m_nFieldIndex]);
    if( it != m_mapLabels.end() )
    {
        // found
        *pValue = static_cast<_s16>((*it).second);
    }
    else
    {
        // not found. try to create a value with that
        std::string token = m_vecTokens[m_nFieldIndex];
        
        if( isDigit(token) ) {
            _s16 nValue;
            std::istringstream(token) >> nValue;
            *pValue = nValue;
        } else {
            // it's a mix, add it to unresolved labels
            m_mapUnresolvedLabels[token].push_back(m_nInstructionCount);
            *pValue = 0;       // to be resolved later
        }
    }

    // return the right next step
    if(m_nCompilationField == INSTR_FIELD_VALUE1)
        return INSTR_FIELD_ADMODE2;
    else
        return INSTR_FIELD_END;
}

// retrieve the token from the pipe and try to determine the addressing mode
Parser::InstructionFields_t Parser::getAdMode(Instruction* pInstr)
{
    DEBUG_ENTER_METHOD

    std::string strField = (m_vecTokens[m_nFieldIndex].substr(0,1));
    InstrADMode_t nValue = m_rISet.getADMode(strField);

    if( nValue == ADMODE_NONE )
        nValue = ADMODE_DEFAULT;     // default value when none
    else
    {
        // remove the addressing mode from the string value
        strField = (m_vecTokens[m_nFieldIndex].substr(1));
        m_vecTokens[m_nFieldIndex] = strField;
    }

    // return the right next step
    if(m_nCompilationField == INSTR_FIELD_ADMODE1)
    {
        pInstr->m_nAdMode1 = nValue;
        return INSTR_FIELD_VALUE1;
    }
    else
    {
        pInstr->m_nAdMode2 = nValue;
        return INSTR_FIELD_VALUE2;
    }
}

// retrieve the token from the pipe and try to determine the instruction modifier
Parser::InstructionFields_t Parser::getModifier(Instruction* pInstr)
{
    DEBUG_ENTER_METHOD

    std::string strModif = m_vecTokens[m_nFieldIndex];
    pInstr->m_nModifier = m_rISet.getModifier(strModif);
    return INSTR_FIELD_ADMODE1;
}

// retrieve the token from the pipe and create an opcode
Parser::InstructionFields_t Parser::getOpcode(Instruction* pInstr)
{
    DEBUG_ENTER_METHOD

    std::string strOpcode = m_vecTokens[m_nFieldIndex];
    pInstr->m_nOpcode = m_rISet.getOpcode(strOpcode);

    if( (m_rISet.getInstructionSetItem(strOpcode))->isModifiable() )
        return INSTR_FIELD_MODIFIER;
    else
        return INSTR_FIELD_ADMODE1;
}

// return true if the string is not numeric
bool Parser::isAlpha(std::string& str)
{
    DEBUG_ENTER_METHOD

    return (!isDigit(str));
}

// return true if the string is only composed with numbers
bool Parser::isDigit(std::string& str)
{
    DEBUG_ENTER_METHOD
    bool bResult = true;
    _uint nStart = 0;
    
    if( str[0] == '-' || str[0] == '+' )
        nStart = 1;

    for(_uint i=nStart;i<str.size();i++)
    {
        if( str[i] < '0' || str[i] > '9' ) {
            bResult = false;
            break;
        }
    }

    return bResult;
}

// return the instruction flow
vecInstructionFlow_t Parser::getInstructionFlow( )
{
    DEBUG_ENTER_METHOD
    return m_vecInstructionFlow;
}

