#ifndef LISPINTERPRETER3_MESSAGETOTHEWORLD_H
#define LISPINTERPRETER3_MESSAGETOTHEWORLD_H

#include "../LispValue.h"

class MessageToTheWorld : public LispValue {
private:
    string msg;
public:
    MessageToTheWorld(string msg) {
        this->msg = msg;
    }

    string to_string() override {
        return msg;
    }
};

#endif //LISPINTERPRETER3_MESSAGETOTHEWORLD_H
