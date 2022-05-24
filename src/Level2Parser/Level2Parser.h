#ifndef LISPINTERPRETER2_LEVEL2PARSER_H
#define LISPINTERPRETER2_LEVEL2PARSER_H

#include "../Level1Parser/Level1Token.h"
#include "Level2Token.h"

namespace Level2Parser
{
    list<Level2Token*> Parse(list<Level1Token> tokens);
    void Print(list<Level2Token*> lisp_values);
}

#endif //LISPINTERPRETER2_LEVEL2PARSER_H
