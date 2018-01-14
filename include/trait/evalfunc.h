#ifndef _SRC_TRAIT_EVALBODY
#define _SRC_TRAIT_EVALBODY

#include "atom/list.h"

template <typename Env, typename T>
struct Eval;

template <typename Env, typename Body>
struct EvalFunc {
    using eval = typename EvalFunc<typename Eval<Env, typename Body::car>::env, typename Body::cdr>::eval;
};

template <typename Env, typename Last>
struct EvalFunc<Env, List<Last>> {
    using eval = typename Eval<Env, Last>::eval;
};

#endif