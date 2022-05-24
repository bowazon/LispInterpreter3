cmake_minimum_required(VERSION 3.5)

project(LispInterpreter3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LispInterpreter3
    main.cpp
        src/Level1Parser/Level1Parser.cpp
        src/Level1Parser/Level1Parser.h
        src/Level1Parser/Level1Token.h src/Eval/LispValue.h src/Level2Parser/Level2Parser.h src/Level2Parser/Level2Parser.cpp src/Level2Parser/Level2Token.h src/Eval/Eval.h src/Eval/Eval.cpp src/Helper.h src/Helper.cpp src/Eval/LispValue/IntLispValue.h src/Eval/LispValue/BoolLispVal.h src/Eval/LispValue/ReservedProcedureLispValue.h src/Eval/LispValue/LambdaLispValue.h src/Eval/LispValue/ErrorLispValue.h src/Eval/Frame.h)
