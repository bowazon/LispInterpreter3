#include "Helper.h"

namespace Helper {

bool IsNumber(string str) {
    for (char c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool IsBoolean(string str) {
    return str.compare("#f") == 0 || str.compare("#t") == 0;
}

bool IsOpeningBrace(char s) {
    return s == '(';
}

bool IsClosingBrace(char s) {
    return s == ')';
}

bool IsNewLineSymbol(char s) {
    return s == '\n';
}

bool IsBlankSymbol(char s) {
    return s == ' ' || s == '\t' || IsNewLineSymbol(s);
}

bool IsBraceSymbol(char s) {
    return IsOpeningBrace(s) || IsClosingBrace(s);
}

}
