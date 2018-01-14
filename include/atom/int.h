#ifndef _SRC_ATOM_INT
#define _SRC_ATOM_INT

template <int N>
struct Int {
    static constexpr const char type[] = "<int>";
    static constexpr int value = N;
};

template <typename L, typename R>
struct IntAdd {
    using apply = Int<L::value + R::value>;
};

template <typename L, typename R>
struct IntSub {
    using apply = Int<L::value - R::value>;
};

template <typename L, typename R>
struct IntMul {
    using apply = Int<L::value * R::value>;
};

template <typename L, typename R>
struct IntDiv {
    using apply = Int<L::value / R::value>;
};

#endif
