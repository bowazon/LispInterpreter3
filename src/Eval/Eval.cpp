#include "Eval.h"
#include "../Level1Parser/Level1Parser.h"
#include "../Level2Parser/Level2Parser.h"
#include "../Helper.h"
#include "LispValue.h"
#include "LispValue/NumberLispValue.h"
#include "LispValue/ReservedProcedureLispValue.h"
#include "LispValue/LambdaLispValue.h"
#include "Frame.h"
#include "Reserved.h"
#include "LispValue/BooleanLispValue.h"
#include <iostream>

//using namespace std;

namespace Eval {

bool IsBuiltIn(string s) {
    return s.compare("+") == 0;
}

bool IsLambda(string s) {
    return s.compare("lambda") == 0;
}

bool IsLambda(Level2Token* token) {
    return IsLambda(next(token->get_unparsed_list().begin())->get_content());
}

bool IsBuiltInFunction(string s) {
    return ProcedureMap.find(s) != ProcedureMap.end();
}

Frame GlobalEnvironment;

// TODO so Lisp Value is really XLispValue.h (implementation of value) and
// IsX(s) method that finds out is this string X.
// This is not the case with Lambda where examined "s" is not a string
// but ... wait...

LispValue* eval(list<Level2Token*> tokens, Frame* frame) {
    if (tokens.size() == 1) {
        Level2Token* crnt = tokens.front();
        if (crnt->get_type() == Level2TokenType::kIdentifier) {
            string s = crnt->get_identif_val();
            if (Helper::IsIntNumber(s)) { // TODO I can pass "s" to all them and maybe make a factory
                return new NumberLispValue(stoi(s));
            }
            if (Helper::IsFloatNumber(s)) {
                return new NumberLispValue(stof(s));
            }
            if (Helper::IsBoolean(s)) {
                return new BooleanLispValue(s);
            }
            if (IsBuiltInFunction(s)) {
                return new ReservedProcedureLispValue(ProcedureMap.find(s)->second);
            }
            // If nothing from above, search in frame or in GlobalEnvironment
            if (frame != nullptr) {
                if (frame->Contains(s)) return frame->FindDefinition(s);
                else if (GlobalEnvironment.Contains(s)) return GlobalEnvironment.FindDefinition(s);
            } else { // TODO we need chain of frames, so if we didn't find something in current frame
                // we should search in previous frame instead of in GlobalEnvironment
                if (GlobalEnvironment.Contains(s)) return GlobalEnvironment.FindDefinition(s);
            }
        } else {
            return eval(Level2Parser::Parse(tokens.front()->get_unparsed_list()), frame);
        }
    } else {
        if (tokens.front()->get_type() == Level2TokenType::kIdentifier &&
                IsLambda(tokens.front()->get_identif_val())) {
            list<Level2Token*> params = Level2Parser::Parse((*next(tokens.begin()))->get_unparsed_list());
            list<Level2Token*> args = Level2Parser::Parse((*next(next(tokens.begin())))->get_unparsed_list());
            return new LambdaLispValue(params, args);
        } else {
            // finally, sort of apply() section
            list<Level2Token*>::iterator it;
            list<LispValue*> operands_values;
            for (it = next(tokens.begin()); it != tokens.end(); ++ it) {
                operands_values.push_back(eval(list<Level2Token*>(1, *it), frame));
            }

            ProcedureLispValue* operat = dynamic_cast<ProcedureLispValue*>(eval(list<Level2Token*>(1, tokens.front()), frame));
            if (operat == nullptr) {
                return new MessageToTheWorld("Not procedure");
            }
            return operat->take_operation(operands_values, eval);
        }
    }

    return new MessageToTheWorld("Unknown problem");
}

void InterpreterCall(string expression) {
    list<Level2Token*> to_eval = Level2Parser::Parse(Level1Parser::Parse(expression));
    cout << ">>>" << expression << endl;
    cout << "..." << eval(to_eval, nullptr)->to_string() << endl;
}

}