#ifndef _SRC_ATOM_LAMBDA
#define _SRC_ATOM_LAMBDA

#include "env.h"

template <typename Params, typename Body, typename Env = EmptyEnv>
struct Closure {
    static constexpr const char type[] = "<closure>";
};

#endif