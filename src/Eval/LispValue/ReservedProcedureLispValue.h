#ifndef LISPINTERPRETER3_RESERVEDPROCEDURELISPVALUE_H
#define LISPINTERPRETER3_RESERVEDPROCEDURELISPVALUE_H

#include "../LispValue.h"

class ReservedProcedureLispValue : public LispValue {
public:
    ReservedProc reserved_proc;
public:
    ReservedProcedureLispValue(ReservedProc reserved_proc) {
        this->reserved_proc = reserved_proc;
    }
    LispValue* take_operation(list<Level2Token*> op, eval eval_call) {
        return reserved_proc(op/*, eval_call*/);
    }
    string to_string() override {
        return "reserved procedure";
    }
};

#endif //LISPINTERPRETER3_RESERVEDPROCEDURELISPVALUE_H
