#ifndef _SRC_TRAIT_TOSTR
#define _SRC_TRAIT_TOSTR

#include "atom/int.h"
#include "atom/list.h"
#include "atom/primitive.h"
#include "atom/sym.h"
#include "atom/closure.h"
#include "atom/bool.h"
#include "util/str.h"

template <typename T>
struct ToStr {};

template <int Gt10, int N>
struct IntToStrHelper {
    using str = typename IntToStrHelper<N / 100, N / 10>::str::template append<'0' + N % 10>;
};

template <int N>
struct IntToStrHelper<0, N> {
    using str = Str<'0' + N % 10>;
};

template <bool Neg, int N>
struct IntToStrNegHelper {
    using str = typename IntToStrHelper<N / 10, N>::str;
};

template <int N>
struct IntToStrNegHelper<true, N> {
    using str = typename IntToStrHelper<-N / 10, -N>::str::template prepend<'-'>;
};

template <typename L>
struct ListToStrHelper {
    using str = typename Cat3<typename ToStr<typename L::car>::str, Str<' '>, typename ListToStrHelper<typename L::cdr>::str>::cat;
};

template <typename E>
struct ListToStrHelper<List<E>> {
    using str = typename ToStr<E>::str;
};

template <>
struct ListToStrHelper<Nil> {
    using str = Str<>;
};

template <int N>
struct ToStr<Int<N>> {
    using str = typename IntToStrNegHelper<(N < 0), N>::str;
};

template <>
struct ToStr<Bool<true>> {
    using str = Str<'#', 't'>;
};

template <>
struct ToStr<Bool<false>> {
    using str = Str<'#', 'f'>;
};

template <char... C>
struct ToStr<Sym<C...>> {
    using str = Str<C...>;
};

template <typename... Elem>
struct ToStr<List<Elem...>> {
    using str = typename Cat3<Str<'('>, typename ListToStrHelper<List<Elem...>>::str, Str<')'>>::cat;
};

template <typename Params, typename Body, typename LEnv>
struct ToStr<Closure<Params, Body, LEnv>> {
    using str = typename Cat3<Str<'(', 'l', 'a', 'm', 'b', 'd', 'a', ' '>, typename Cat3<typename ToStr<Params>::str, Str<' '>, typename ListToStrHelper<Body>::str>::cat, Str<')'>>::cat;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Plus, LEnv>> {
    using str = Str<'+'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Minus, LEnv>> {
    using str = Str<'-'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Multiply, LEnv>> {
    using str = Str<'*'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Divide, LEnv>> {
    using str = Str<'/'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Car, LEnv>> {
    using str = Str<'c', 'a', 'r'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Cdr, LEnv>> {
    using str = Str<'c', 'd', 'r'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Cons, LEnv>> {
    using str = Str<'c', 'o', 'n', 's'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Define, LEnv>> {
    using str = Str<'d', 'e', 'f', 'i', 'n', 'e'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, If, LEnv>> {
    using str = Str<'i', 'f'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Eq, LEnv>> {
    using str = Str<'e', 'q'>;
};

template <typename LEnv>
struct ToStr<Closure<Nil, Lambda, LEnv>> {
    using str = Str<'l', 'a', 'm', 'b', 'd', 'a'>;
};

#endif
