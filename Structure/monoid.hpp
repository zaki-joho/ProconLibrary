#include "../bits/stdc++.h"
struct RangeMinimumQuery
{
    using type = int;
    static type id() { return INT_MAX; }
    static type op(const type &l, const type &r) { return std::min(l, r); }
};

struct RangeMaximumQuery
{
    using type = int;
    static type id() { return -INT_MAX; }
    static type op(const type &l, const type &r) { return std::max(l, r); }
};
