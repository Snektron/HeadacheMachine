#ifndef _SRC_UTIL_TOSTR
#define _SRC_UTIL_TOSTR

template <char... S>
struct Str {
    static constexpr const char value[] = {S...};

    template <char C>
    using prepend = Str<C, S...>;

    template <char C>
    using append = Str<S..., C>;
};

template <typename S1, typename S2>
struct Cat {};

template <char... S1, char... S2>
struct Cat<Str<S1...>, Str<S2...>> {
    using cat = Str<S1..., S2...>;
};

template <typename S1, typename S2, typename S3>
struct Cat3 {};

template <char... S1, char... S2, char... S3>
struct Cat3<Str<S1...>, Str<S2...>, Str<S3...>> {
    using cat = Str<S1..., S2..., S3...>;
};

#endif
