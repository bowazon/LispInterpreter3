#ifndef LISPINTERPRETER3_ERRORLISPVALUE_H
#define LISPINTERPRETER3_ERRORLISPVALUE_H

#include "../LispValue.h"

class ErrorLispValue : public LispValue {
private:
    string msg;
public:
    ErrorLispValue(string msg) {
        this->msg = msg;
    }
    LispValue* take_operation(list<LispValue*> operands, eval eval_call) override { // TODO now it's superstupids
        return nullptr;
    }
    string to_string() override {
        return msg;
    }
};

#endif //LISPINTERPRETER3_ERRORLISPVALUE_H
