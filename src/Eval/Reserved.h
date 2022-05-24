#ifndef LISPINTERPRETER3_RESERVED_H
#define LISPINTERPRETER3_RESERVED_H

#include "LispValue.h"
#include <map>
#include <string>

using namespace std;

extern map<string, ReservedProc> ProcedureMap;

#endif //LISPINTERPRETER3_RESERVED_H
