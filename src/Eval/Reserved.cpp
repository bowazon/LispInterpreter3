#include <iostream>
#include "Reserved.h"
#include "LispValue/NumberLispValue.h"
#include "LispValue/BooleanLispValue.h"
#include "LispValue/MessageToTheWorld.h"

LispValue* ProcPlus(list<LispValue*> args) {
    list<LispValue*>::iterator it;
    NumberLispValue* retval = new NumberLispValue(0);
    for (it = args.begin(); it != args.end(); ++it) {
        NumberLispValue* number = dynamic_cast<NumberLispValue *>(*it);
        if (number == nullptr)
            throw NotThatValueException(); // or return ErrorLispValue
        retval->add(number);
    }

    return retval;
}

LispValue* ProcMinus(list<LispValue*> args) {
    list<LispValue*>::iterator it;
    NumberLispValue* retval = dynamic_cast<NumberLispValue *>(*args.begin());
    if (retval == nullptr)
        throw NotThatValueException();

    if (args.size() == 1) {
        retval->negate();
        return retval;
    }

    for (it = next(args.begin()); it != args.end(); ++it) {
        NumberLispValue* number = dynamic_cast<NumberLispValue *>(*it);
        if (number == nullptr)
            throw NotThatValueException();
        retval->sub(number);
    }
    return retval;
}

LispValue* ProcMultiply(list<LispValue*> args) {
    list<LispValue*>::iterator it;
    NumberLispValue* retval = new NumberLispValue(1);
    for (it = args.begin(); it != args.end(); ++it) {
        NumberLispValue* number = dynamic_cast<NumberLispValue *>(*it);
        if (number == nullptr)
            throw NotThatValueException(); // or return ErrorLispValue
        retval->mul(number);
    }

    return retval;
}

// TODO can't divide with one argument or three or more
LispValue* ProcDivide(list<LispValue*> args) {
    list<LispValue*>::iterator it;
    NumberLispValue* retval = dynamic_cast<NumberLispValue *>(*args.begin());
    if (retval == nullptr)
        throw NotThatValueException();
    for (it = next(args.begin()); it != args.end(); ++it) {
        NumberLispValue* number = dynamic_cast<NumberLispValue *>(*it);
        if (number == nullptr)
            throw NotThatValueException();
        retval->div(number);
    }
    return retval;
}

// TODO drawback here: we must iterate through all boolean values to return result,
// however one false value would be enough to turn all expression to false
LispValue* ProcAnd(list<LispValue*> args) {
    list<LispValue*>::iterator it;
    BooleanLispValue* retval = dynamic_cast<BooleanLispValue *>(*args.begin());
    if (retval == nullptr)
        throw NotThatValueException();
    for (it = next(args.begin()); it != args.end(); ++it) {
        BooleanLispValue* b = dynamic_cast<BooleanLispValue *>(*it);
        if (b == nullptr)
            throw NotThatValueException();
        retval->logic_and(b);
    }

    return retval;
}

LispValue* ProcOr(list<LispValue*> args) {
    list<LispValue*>::iterator it;
    BooleanLispValue* retval = dynamic_cast<BooleanLispValue *>(*args.begin());
    if (retval == nullptr)
        throw NotThatValueException();
    for (it = next(args.begin()); it != args.end(); ++it) {
        BooleanLispValue* b = dynamic_cast<BooleanLispValue *>(*it);
        if (b == nullptr)
            throw NotThatValueException();
        retval->logic_or(b);
    }

    return retval;
}

// TODO check for one argument
LispValue* ProcNot(list<LispValue*> args) {
    list<LispValue*>::iterator it;
    BooleanLispValue* retval = dynamic_cast<BooleanLispValue *>(*args.begin());
    if (retval == nullptr)
        throw NotThatValueException();

    retval->logic_not();

    return retval;
}

LispValue* ProcMore(list<LispValue*> args) {
    NumberLispValue* first = dynamic_cast<NumberLispValue *>(*args.begin());
    NumberLispValue* second = dynamic_cast<NumberLispValue *>(*next(args.begin()));
    if (first == nullptr || second == nullptr)
        throw NotThatValueException();
    return new BooleanLispValue(first->IsMore(second));
}

LispValue* ProcLess(list<LispValue*> args) {
    NumberLispValue* first = dynamic_cast<NumberLispValue *>(*args.begin());
    NumberLispValue* second = dynamic_cast<NumberLispValue *>(*next(args.begin()));
    if (first == nullptr || second == nullptr)
        throw NotThatValueException();
    return new BooleanLispValue(first->IsLess(second));
}

LispValue* ProcEqual(list<LispValue*> args) {
    NumberLispValue* first = dynamic_cast<NumberLispValue *>(*args.begin());
    NumberLispValue* second = dynamic_cast<NumberLispValue *>(*next(args.begin()));
    if (first == nullptr || second == nullptr)
        throw NotThatValueException();
    return new BooleanLispValue(first->IsEqual(second));
}

LispValue* ProcDefine(list<LispValue*> args) {
    //string name = args.front().;
    //GlobalEnvironment.Define();
    return new MessageToTheWorld("defined");
}

map<string, ReservedProc> ProcedureMap = {
    {"+", ProcPlus},
    {"-", ProcMinus},
    {"*", ProcMultiply},
    {"/", ProcDivide},
    {">", ProcMore},
    {"<", ProcLess},
    {"=", ProcEqual},
    {"and", ProcAnd},
    {"or", ProcOr},
    {"not", ProcNot},
    {"define", ProcDefine},
};