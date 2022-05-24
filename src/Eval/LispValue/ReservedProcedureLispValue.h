#ifndef LISPINTERPRETER3_RESERVEDPROCEDURELISPVALUE_H
#define LISPINTERPRETER3_RESERVEDPROCEDURELISPVALUE_H

#include "../LispValue.h"

class ReservedProcedureLispValue : public ProcedureLispValue {
public:
    ReservedProc reserved_proc;
public:
    ReservedProcedureLispValue(ReservedProc reserved_proc) {
        this->reserved_proc = reserved_proc;
    }
    LispValue* take_operation(list<LispValue*> operands, eval eval_call) override {
        return reserved_proc(operands/*, eval_call*/);
    }
    string to_string() override {
        return "reserved procedure";
    }
};

#endif //LISPINTERPRETER3_RESERVEDPROCEDURELISPVALUE_H
