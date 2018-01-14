#ifndef _SRC_TRAIT_APPLY
#define _SRC_TRAIT_APPLY

#include "atom/closure.h"
#include "trait/evalfunc.h"
#include "env.h"

template <typename Env, typename T>
struct Eval;

template <typename Env, typename Args, typename F>
struct Apply {};

template <typename Env, typename Args, typename Params, typename Body, typename LEnv>
struct Apply<Env, Args, Closure<Params, Body, LEnv>> {
    using apply = typename EvalFunc<typename EnvBind<Params, Args, typename EnvMerge<Env, LEnv>::merge>::bind, Body>::eval;
};

template <typename Env, typename Args, typename LEnv>
struct Apply<Env, Args, Closure<Nil, Plus, LEnv>> {
    using apply = typename ListFold<typename Args::cdr, IntAdd, typename Args::car>::accum;
};

template <typename Env, typename Args, typename LEnv>
struct Apply<Env, Args, Closure<Nil, Minus, LEnv>> {
    using apply = typename ListFold<typename Args::cdr, IntSub, typename Args::car>::accum;
};

template <typename Env, typename Args, typename LEnv>
struct Apply<Env, Args, Closure<Nil, Multiply, LEnv>> {
    using apply = typename ListFold<typename Args::cdr, IntMul, typename Args::car>::accum;
};

template <typename Env, typename Args, typename LEnv>
struct Apply<Env, Args, Closure<Nil, Divide, LEnv>> {
    using apply = typename ListFold<typename Args::cdr, IntDiv, typename Args::car>::accum;
};

template <typename Env, typename Args, typename LEnv>
struct Apply<Env, Args, Closure<Nil, Car, LEnv>> {
    using apply = typename Args::car::car;
};

template <typename Env, typename Args, typename LEnv>
struct Apply<Env, Args, Closure<Nil, Cdr, LEnv>> {
    using apply = typename Args::car::cdr;
};

template <typename Env, typename H, typename... T, typename LEnv>
struct Apply<Env, List<H, List<T...>>, Closure<Nil, Cons, LEnv>> {
    using apply = List<H, T...>;
};

template <typename Env, typename H, typename T, typename LEnv>
struct Apply<Env, List<H, T>, Closure<Nil, Cons, LEnv>> {
    using apply = List<H, T>;
};

template <typename Env, typename X, typename Y, typename LEnv>
struct Apply<Env, List<X, Y>, Closure<Nil, Eq, LEnv>> {
    using apply = Bool<false>;
};

template <typename Env, typename X, typename LEnv>
struct Apply<Env, List<X, X>, Closure<Nil, Eq, LEnv>> {
    using apply = Bool<true>;
};

#endif