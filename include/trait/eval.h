#ifndef _SRC_TRAITS_EVAL
#define _SRC_TRAITS_EVAL

#include "atom/int.h"
#include "atom/sym.h"
#include "atom/closure.h"
#include "atom/list.h"
#include "atom/primitive.h"
#include "atom/bool.h"
#include "trait/apply.h"
#include "trait/evallist.h"

template <typename Env, typename T>
struct Eval {};

template <typename Env, int N>
struct Eval<Env, Int<N>> {
    using eval = Int<N>;
    using env = Env;
};

template <typename Env, bool B>
struct Eval<Env, Bool<B>> {
    using eval = Bool<B>;
    using env = Env;
};

template <typename Env, char... C>
struct Eval<Env, Sym<C...>> {
    using eval = typename EnvFind<Env, Sym<C...>>::find;
    using env = Env;
};

template <typename Env, typename Head, typename... Tail>
struct Eval<Env, List<Head, Tail...>> {
    using eval = typename Apply<Env, typename EvalList<Env, List<Tail...>>::eval, typename Eval<Env, Head>::eval>::apply;
    using env = Env;
};

template <typename Env, char... C, typename... Tail>
struct Eval<Env, List<Sym<C...>, Tail...>> {
    using expr = Eval<Env, List<typename Eval<Env, Sym<C...>>::eval, Tail...>>;
    using eval = typename expr::eval;
    using env = typename expr::env;
};

template <typename Env, typename LEnv, typename Expr, char... C>
struct Eval<Env, List<Closure<Nil, Define, LEnv>, Sym<C...>, Expr>> {
    using eval = Nil;
    using env = typename Env::template insert<Sym<C...>, typename Eval<Env, Expr>::eval>;
};

template <typename Env, typename LEnv, typename Param, typename Expr>
struct Eval<Env, List<Closure<Nil, Define, LEnv>, Param, Expr>> {
    using eval = Nil;
    using env = typename Env::template insert<typename Param::car, Closure<typename Param::cdr, List<Expr>>>;
};

template <typename Env, typename Cond, typename Csq, typename Alt>
struct IfHelper {
    using eval = typename Eval<Env, Csq>::eval;
};

template <typename Env, typename Csq, typename Alt>
struct IfHelper<Env, Bool<false>, Csq, Alt> {
    using eval = typename Eval<Env, Alt>::eval;
};

template <typename Env, typename LEnv, typename Cond, typename Csq, typename Alt>
struct Eval<Env, List<Closure<Nil, If, LEnv>, Cond, Csq, Alt>> {
    using eval = typename IfHelper<Env, typename Eval<Env, Cond>::eval, Csq, Alt>::eval;
    using env = Env;
};

template <typename Env, typename LEnv, typename Param, typename... Body>
struct Eval<Env, List<Closure<Nil, Lambda, LEnv>, Param, Body...>> {
    using eval = Closure<Param, List<Body...>, LEnv>;
    using env = Env;
};

template <typename Env>
struct Eval<Env, Nil> {
    using eval = Nil;
    using env = Env;
};

template <typename Env, typename Params, typename Body, typename LEnv>
struct Eval<Env, Closure<Params, Body, LEnv>> {
    using eval = Closure<Params, Body, typename EnvMerge<Env, LEnv>::merge>;
    using env = Env;
};

#endif
