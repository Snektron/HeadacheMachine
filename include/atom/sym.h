#ifndef _SRC_ATOM_VAR
#define _SRC_ATOM_VAR

template <char... C>
struct Sym {
    static constexpr const char type[] = "<sym>";

    static constexpr const char name[] = {C...};
};

#endif
