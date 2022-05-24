#include "Level1Parser.h"
#include "../Helper.h"
#include <iostream>

using namespace Helper;

namespace Level1Parser {

bool IsNameTrackingStopSymbol(char s);

list<Level1Token> Parse(const string &s_expr) { // TODO is it ok to return list like this?
    list<Level1Token> result;
    int identifier_starting_pos = -1;
    int brace_cntr = 0;

    for (int i = 0; i < s_expr.length(); i++) {
        char symb = s_expr.at(i);
        if (IsNameTrackingStopSymbol(symb)) {
            if (identifier_starting_pos != -1) {
                int length = i - identifier_starting_pos;
                result.push_back(Level1Token(s_expr.substr(identifier_starting_pos, length)));
                identifier_starting_pos = -1;
            }
        } else {
            if (identifier_starting_pos == -1) {
                identifier_starting_pos = i;
            }
        }
        if (IsBraceSymbol(symb)) {
            result.push_back(Level1Token(symb));
            if (IsOpeningBrace(symb)) brace_cntr++;
            if (IsClosingBrace(symb)) brace_cntr--;
            continue;
        }
    }

    // Suppose we want to parse just "foo", then we will exit previous cycle
    // before putting token to list.
    // So after exiting cycle we must to check if
    // name_starting_pos -1 or not and if not, then that means we started to
    // record something and didn't finished it
    if (identifier_starting_pos != -1) {
        result.push_back(Level1Token(s_expr.substr(identifier_starting_pos, s_expr.length())));
    }

    return result;
}

void Print(list<Level1Token> tokens) {
    list<Level1Token>::iterator it;
    cout << "..." << endl;
    int i = 0;
    for (it = tokens.begin(); it != tokens.end(); ++it, i++) {
        cout << "Level 1 token " << i << ": \"" << it->get_content() << "\"" << endl;
    }
}

bool IsNameTrackingStopSymbol(char s) {
    return IsBlankSymbol(s) || IsBraceSymbol(s);
}

} // namespace Level1Parser
