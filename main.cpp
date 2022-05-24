#include "src/Eval/Eval.h"

using namespace std;
using namespace Eval;

int main()
{
    //Eval::InterpreterCall("(+ 2 3 (+ 4 7))");
    //Eval::InterpreterCall("(define a (+ 3 5)))");
    //Eval::InterpreterCall("a");
    //Eval::InterpreterCall("(+ 2 3 (+ 1 5))");
    Eval::InterpreterCall("((lambda (x y) (+ x y)) 3 5)");
    return 0;
}
