#ifndef _SRC_TRAIT_EVALLIST
#define _SRC_TRAIT_EVALLIST

template <typename Env, typename T>
struct Eval;

template <typename Env, typename L>
struct EvalList {
    using eval = typename EvalList<Env, typename L::cdr>::eval::template push<typename Eval<Env, typename L::car>::eval>;
};

template <typename Env>
struct EvalList<Env, Nil> {
    using eval = Nil;
};

#endif