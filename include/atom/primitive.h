#ifndef _SRC_ATOM_PRIMITIVE
#define _SRC_ATOM_PRIMITIVE

#include "env.h"
#include "closure.h"
#include "sym.h"
#include "list.h"

struct Plus {};

struct Minus {};

struct Multiply {};

struct Divide {};

struct Define {};

struct Car {};

struct Cdr {};

struct Cons {};

struct If {};

struct Eq {};

struct Lambda {};

using Primitives = EmptyEnv
    ::insert<Sym<'+'>, Closure<Nil, Plus>>
    ::insert<Sym<'-'>, Closure<Nil, Minus>>
    ::insert<Sym<'*'>, Closure<Nil, Multiply>>
    ::insert<Sym<'/'>, Closure<Nil, Divide>>
    ::insert<Sym<'d', 'e', 'f', 'i', 'n', 'e'>, Closure<Nil, Define>>
    ::insert<Sym<'c', 'a', 'r'>, Closure<Nil, Car>>
    ::insert<Sym<'c', 'd', 'r'>, Closure<Nil, Cdr>>
    ::insert<Sym<'c', 'o', 'n', 's'>, Closure<Nil, Cons>>
    ::insert<Sym<'i', 'f'>, Closure<Nil, If>>
    ::insert<Sym<'e', 'q'>, Closure<Nil, Eq>>
    ::insert<Sym<'l', 'a', 'm', 'b', 'd', 'a'>, Closure<Nil, Lambda>>;

#endif
