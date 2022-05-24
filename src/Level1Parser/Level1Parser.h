#ifndef LEVEL1PARSER_H
#define LEVEL1PARSER_H

#include "Level1Token.h"
#include <string>
#include <list>

using namespace std;

namespace Level1Parser {
    // Example: "(+ abc (* 3 5 ) )  " will be parsed to tokens "(", "+",
    // "abc", "(", "*", "3", "5", ")", ")". All blank symbols will be ignored.
    list<Level1Token> Parse(const string &s_expr);
    void Print(list<Level1Token> tokens);
}

#endif // LEVEL1PARSER_H
