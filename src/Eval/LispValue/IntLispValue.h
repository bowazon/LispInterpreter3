#ifndef LISPINTERPRETER3_INTLISPVALUE_H
#define LISPINTERPRETER3_INTLISPVALUE_H

#include "../LispValue.h"

class IntLispValue : public LispValue {
private:
    int val;
public:
    IntLispValue(int val) {
        this->val = val;
    }
    int get_val() {
        return val;
    }
    string to_string() override {
        return std::to_string(val);
    }
};

#endif
