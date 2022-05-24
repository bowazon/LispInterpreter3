#include "Eval.h"
#include "../Level1Parser/Level1Parser.h"
#include "../Level2Parser/Level2Parser.h"
#include "../Helper.h"
#include "LispValue.h"
#include "LispValue/IntLispValue.h"
#include "LispValue/ReservedProcedureLispValue.h"
#include "LispValue/LambdaLispValue.h"
#include "Frame.h"
#include <iostream>

//using namespace std;

namespace Eval {

list<Level2Token*> rest(list<Level2Token*> my_list) { // TODO how da fuck get sublist from second to end???
    list<Level2Token*>::iterator it;
    list<Level2Token*> retval;
    for(it = next(my_list.begin()); it != my_list.end(); ++it) {
        retval.push_back(*it);
    }
    return retval;
}

bool IsBuiltIn(string s) {
    return s.compare("+") == 0;
}

// TODO I think it shouldn't carry eval() because otherwise it should also carry frames.
LispValue* plusProc(list<Level2Token*> tokens) {
    list<Level2Token*>::iterator it;
    int val = 0;
    for (it = tokens.begin(); it != tokens.end(); ++it) {
        Level2Token* crnt_token = *it;
        IntLispValue* number = dynamic_cast<IntLispValue *>(crnt_token);
        if (number == nullptr)
            throw NotThatValueException(); // or return ErrorLispValue
        val += number->get_val();
    }

    return new IntLispValue(val);
}

bool IsLambda(string s) {
    return s.compare("lambda") == 0;
}

bool IsLambda(Level2Token* token) {
    return IsLambda(next(token->get_unparsed_list().begin())->get_content());
}
/*
LispValue* apply(Level2Token* op, list<Level2Token*> tokens, Frame* frame); // TODO apply shouldn't
                                                                          // carry frame
                                                              // or should? it calls eval()
*/
Frame GlobalEnvironment;

LispValue* eval(list<Level2Token*> tokens, Frame* frame) {
    if (tokens.size() == 1) {
        Level2Token* crnt = tokens.front();
        if (crnt->get_type() == Level2TokenType::kIdentifier) {
            string s = crnt->get_identif_val();
            if (Helper::IsNumber(s)) { // TODO I can pass "s" to all them and maybe make a factory
                return new IntLispValue(stoi(s));
            }
            if (IsBuiltIn(s)) {
                return new ReservedProcedureLispValue(plusProc);
            }
            // If nothing from above, search in frame or in GlobalEnvironment
            if (frame != nullptr) {
                if (frame->Contains(s)) return eval(list<Level2Token*>(1, frame->FindDefinition(s)), nullptr);
                else if (GlobalEnvironment.Contains(s)) return eval(list<Level2Token*>(1, GlobalEnvironment.FindDefinition(s)), nullptr);
            } else { // TODO we need chain of frames, so if we didn't find something in current frame
                // we should search in previous frame instead of in GlobalEnvironment
                if (GlobalEnvironment.Contains(s)) return eval(list<Level2Token*>(1, GlobalEnvironment.FindDefinition(s)), nullptr);
            }
        } else if (IsLambda(crnt)) {
            list<Level2Token*> lambda = Level2Parser::Parse(tokens.front()->get_unparsed_list());
            list<Level2Token*> params = Level2Parser::Parse((*next(lambda.begin()))->get_unparsed_list());
            list<Level2Token*> args = Level2Parser::Parse((*next(next(lambda.begin())))->get_unparsed_list());
            return new LambdaLispValue(params, args);
        } else {
            return eval(Level2Parser::Parse(tokens.front()->get_unparsed_list()), frame);
        }
    } else {
        // this is sort of apply() section
        auto operands = rest(tokens);
        list<Level2Token*>::iterator it;
        //return apply(tokens.front(), operands, frame);
        for (it = operands.begin(); it != operands.end(); ++ it) {

        }
        return eval(list<Level2Token*>(1, tokens.front()), frame)->take_operation(operands, eval);
    }
}
/*
LispValue* apply(Level2Token* op, list<Level2Token*> operands, Frame* frame) {
    return eval(list<Level2Token*>(1, op), frame)->take_operation(operands, eval);
}
 */

void InterpreterCall(string expression) {
    list<Level2Token*> to_eval = Level2Parser::Parse(Level1Parser::Parse(expression));
    cout << ">>>" << expression << endl;
    cout << "..." << eval(to_eval, nullptr)->to_string() << endl;
}

}