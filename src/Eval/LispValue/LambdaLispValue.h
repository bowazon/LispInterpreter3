#ifndef LISPINTERPRETER3_LAMBDALISPVALUE_H
#define LISPINTERPRETER3_LAMBDALISPVALUE_H

#include <iostream>
#include "../LispValue.h"
#include "ErrorLispValue.h"
#include "../../Level2Parser/Level2Parser.h"
#include "../../Level1Parser/Level1Parser.h"

class LambdaLispValue : public LispValue {
public:
    list<Level2Token*> parameters;
    list<Level2Token*> body;
public:
    LambdaLispValue(list<Level2Token*> parameters, list<Level2Token*> body) {
        this->parameters = parameters;
        this->body = body;
    }
    LispValue* take_operation(list<Level2Token*> args, eval eval_call) override {
        // TODO here I want manually substitute parameters with arguments in lambda body.
        // But what if better way is implement eval frames here?
        // So for example if I want to eval ((lambda (x y) (+ x y)) 3 5) it's
        // like call eval on (+ x y) in frame where (define x 3) and (define y 5).
        // The reason to do this: the body could introduce new context with
        // another x and y so simply substituting them will be wrong

        Frame frame;
        list<Level2Token*>:: iterator param_it, args_it;
        param_it = parameters.begin();
        for (args_it = args.begin(); args_it != args.end(); ++args_it, ++param_it) {
            frame.Define((*param_it)->get_identif_val(), (*args_it));
        }

        return eval_call(body, &frame);

        // TODO we really need checks here
        // 1) amount of args should be equal amount of params
        // 2) params should be identifiers, not lists
        return new ErrorLispValue("tmp");
    }
    string to_string() override {
        return "lambda";
    }
};

#endif //LISPINTERPRETER3_LAMBDALISPVALUE_H
