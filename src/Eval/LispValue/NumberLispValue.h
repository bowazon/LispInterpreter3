#ifndef LISPINTERPRETER3_NUMBERLISPVALUE_H
#define LISPINTERPRETER3_NUMBERLISPVALUE_H

#include "../LispValue.h"

class NumberLispValue : public LispValue {
private:
    enum NumberType {kInteger, kFloat};
    NumberType type;
    int int_val = 0;
    float float_val = 0;

public:
    NumberLispValue(int int_val) {
        this->type = kInteger;
        this->int_val = int_val;
    }

    NumberLispValue(float float_val) {
        this->type = kFloat;
        this->float_val = float_val;
    }

    void add(NumberLispValue* n) { // TODO hell
        switch (this->type) {
            case kInteger: {
                if (n->type == kInteger) this->int_val += n->int_val;
                if (n->type == kFloat) {
                    this->type = kFloat;
                    this->float_val = this->int_val + n->float_val;
                }
                break;
            }
            case kFloat: {
                if (n->type == kFloat) this->float_val += n->float_val;
                if (n->type == kInteger) this->float_val += n->int_val;
                break;
            }
        }
    }

    void sub(NumberLispValue* n) {
        switch (this->type) {
            case kInteger: {
                if (n->type == kInteger) this->int_val -= n->int_val;
                if (n->type == kFloat) {
                    this->type = kFloat;
                    this->float_val = this->int_val - n->float_val;
                }
                break;
            }
            case kFloat: {
                if (n->type == kFloat) this->float_val -= n->float_val;
                if (n->type == kInteger) this->float_val -= n->int_val;
                break;
            }
        }
    }

    void div(NumberLispValue* n) {
        switch (this->type) {
            case kInteger: {
                if (n->type == kInteger) this->int_val /= n->int_val;
                if (n->type == kFloat) {
                    this->type = kFloat;
                    this->float_val = this->int_val / n->float_val;
                }
                break;
            }
            case kFloat: {
                if (n->type == kFloat) this->float_val /= n->float_val;
                if (n->type == kInteger) this->float_val /= n->int_val;
                break;
            }
        }
    }

    void mul(NumberLispValue* n) {
        switch (this->type) {
            case kInteger: {
                if (n->type == kInteger) this->int_val *= n->int_val;
                if (n->type == kFloat) {
                    this->type = kFloat;
                    this->float_val = this->int_val * n->float_val;
                }
                break;
            }
            case kFloat: {
                if (n->type == kFloat) this->float_val *= n->float_val;
                if (n->type == kInteger) this->float_val *= n->int_val;
                break;
            }
        }
    }

    void negate() {
        switch (this->type) {
            case kInteger: {
                this->int_val = -this->int_val;
                break;
            }
            case kFloat: {
                this->float_val = -this->float_val;
                break;
            }
        }
    }

    bool IsMore(NumberLispValue* n) {
        switch (this->type) {
            case kInteger: {
                if (n->type == kInteger) return (this->int_val) > (n->int_val);
                if (n->type == kFloat) return (this->int_val) > (n->float_val);
                break;
            }
            case kFloat: {
                if (n->type == kFloat) return (this->float_val) > (n->float_val);
                if (n->type == kInteger) return (this->float_val) > (n->int_val);
                break;
            }
        }
    }

    bool IsLess(NumberLispValue* n) {
        switch (this->type) {
            case kInteger: {
                if (n->type == kInteger) return (this->int_val) < (n->int_val);
                if (n->type == kFloat) return (this->int_val) < (n->float_val);
                break;
            }
            case kFloat: {
                if (n->type == kFloat) return (this->float_val) < (n->float_val);
                if (n->type == kInteger) return (this->float_val) < (n->int_val);
                break;
            }
        }
    }

    bool IsEqual(NumberLispValue* n) {
        switch (this->type) {
            case kInteger: {
                if (n->type == kInteger) return (this->int_val) == (n->int_val);
                if (n->type == kFloat) return (this->int_val) == (n->float_val); // TODO no this way
                break;
            }
            case kFloat: {
                if (n->type == kFloat) return (this->float_val) == (n->float_val);
                if (n->type == kInteger) return (this->float_val) == (n->int_val);
                break;
            }
        }
    }

    string to_string() override {
        if (type == kInteger) return std::to_string(int_val);
        return std::to_string(float_val);
    }
};

#endif
