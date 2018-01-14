# HeadacheMachine
LISP to C++ template transpiler

## Compiling the transpiler

Run `make`

## Usage

To compile a lisp program to a standalone source file, run
```
headache -s -i <lisp file> -o <output file>
```
Compile that using
```
g++ -o<executable> -std=c++17 -Iinclude/ <output file>.cpp
```

## Built-in functions

Currently built-in functions are
* Operators +, -, *, /
* define (both functions and variables)
* car
* cdr
* cons
* if
* eq
* lambda