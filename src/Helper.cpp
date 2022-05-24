#include "Helper.h"

namespace Helper {

bool IsIntNumber(string str) {
    for (char c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool IsFloatNumber(string str) {
    int dot_counter = 0;
    for (char c : str) {
        if (c == '.') {
            dot_counter++;
            continue;
        }
        if (std::isdigit(c) == 0) return false;
    }
    return dot_counter == 1;
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
