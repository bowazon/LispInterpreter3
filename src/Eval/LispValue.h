#ifndef LISPINTERPRETER2_LISPVALUE_H
#define LISPINTERPRETER2_LISPVALUE_H

#include "../Level1Parser/Level1Token.h"
#include "../Level2Parser/Level2Token.h"
#include "Frame.h"
#include <list>

using namespace std;

class NotThatValueException : public std::exception {};

class LispValue;

typedef LispValue* (*eval) (list<Level2Token*>, Frame* frame);
typedef LispValue* (*ReservedProc) (list<Level2Token*> l);

class LispValue {
public:
    virtual LispValue* take_operation(list<Level2Token*> op, eval eval_call) = 0;
    virtual string to_string() = 0;
};



#endif //LISPINTERPRETER2_LISPVALUE_H
