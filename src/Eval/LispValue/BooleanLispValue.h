#ifndef LISPINTERPRETER3_BOOLEANLISPVALUE_H
#define LISPINTERPRETER3_BOOLEANLISPVALUE_H

#include "../LispValue.h"

class BooleanLispValue : public LispValue {
private:
    bool val;
public:
    BooleanLispValue(bool val) {
        this->val = val;
    }
    BooleanLispValue(string s) {
        if (s == "#t"){
            this->val = true;
        } else if (s == "#f") {
            this->val = false;
        } else throw NotThatValueException();
    }
    void logic_and(BooleanLispValue* b) {
        this->val &= b->val;
    }
    void logic_or(BooleanLispValue* b) {
        this->val |= b->val;
    }
    void logic_not() {
        this->val = !this->val;
    }
    string to_string() override {
        if (this->val) return "#t";
        return "#f";
    }
};

#endif //LISPINTERPRETER3_BOOLEANLISPVALUE_H
