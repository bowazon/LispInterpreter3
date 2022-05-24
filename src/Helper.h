#ifndef LISPINTERPRETER2_HELPER_H
#define LISPINTERPRETER2_HELPER_H

#include <string>

using namespace std;

namespace Helper {
    bool IsNumber(string str);
    bool IsBoolean(string str);
    bool IsNewLineSymbol(char s);
    bool IsBlankSymbol(char s);
    bool IsBraceSymbol(char s);
    bool IsOpeningBrace(char s);
    bool IsClosingBrace(char s);
}


#endif //LISPINTERPRETER2_HELPER_H
