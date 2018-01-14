#ifndef _SRC_ENV
#define _SRC_ENV

#include "atom/list.h"

template <typename K, typename V>
struct Binding {
    using key = K;
    using value = V;
};

template <typename... B>
struct Env {};

template <typename H, typename... T>
struct Env<H, T...> {
    template <typename K, typename V>
    using insert = Env<Binding<K, V>, H, T...>;

    using head = H;
    using tail = Env<T...>;
};

template <>
struct Env<> {
    template <typename K, typename V>
    using insert = Env<Binding<K, V>>;
};

using EmptyEnv = Env<>;

template <typename Env, typename Key>
struct EnvFind {
    using find = typename EnvFind<typename Env::tail, Key>::find;
};

template <typename Key, typename Value, typename... T>
struct EnvFind<Env<Binding<Key, Value>, T...>, Key> {
    using find = Value;
};

template <typename A, typename B>
struct EnvMerge {};

template <typename... BindingsA, typename... BindingsB>
struct EnvMerge<Env<BindingsA...>, Env<BindingsB...>> {
    using merge = Env<BindingsA..., BindingsB...>;
};

template <typename Params, typename Args, typename EnvA>
struct EnvBind {
    using bind = typename EnvBind<typename Params::cdr, typename Args::cdr, typename EnvA::tail>::bind::template insert<typename Params::car, typename Args::car>;
};

template <typename EnvA>
struct EnvBind<Nil, Nil, EnvA> {
    using bind = EnvA;
};

#endif
