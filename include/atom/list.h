#ifndef _SRC_ATOM_LIST
#define _SRC_ATOM_LIST

template <typename... Elems>
struct List {};

template <typename Head, typename... Tail>
struct List<Head, Tail...> {
    static constexpr const char type[] = "<list>";

    using car = Head;
    using cdr = List<Tail...>;

    template <typename New>
    using push = List<New, Head, Tail...>;

    template <typename New>
    using append = List<Head, Tail..., New>;
};

template <>
struct List<> {
    static constexpr const char type[] = "<nil>";

    template <typename New>
    using push = List<New>;

    template <typename New>
    using append = List<New>;
};

using Nil = List<>;

template <typename L, template<typename, typename> typename F, typename Init>
struct ListFold {
    using accum = typename F<typename ListFold<typename L::cdr, F, Init>::accum, typename L::car>::apply;
};

template <template<typename, typename> typename F, typename Init>
struct ListFold<Nil, F, Init> {
    using accum = Init;
};

#endif
