#ifndef _SRC_ATOM_BOOL
#define _SRC_ATOM_BOOL

template <bool B>
struct Bool {
    static constexpr const char type[] = "<bool>";
    static constexpr bool value = B;
};

#endif
