#include "../../bits/stdc++.h"
// SegmentTree / DisjointSparseTable に載せるモノイド
struct RangeMinimumQuery {
    using type = int;
    static type id() { return INT_MAX; }
    static type op(const type &l, const type &r) { return std::min(l, r); }
};

struct RangeMaximumQuery {
    using type = int;
    static type id() { return -INT_MAX; }
    static type op(const type &l, const type &r) { return std::max(l, r); }
};

struct RangeSumQuery {
    using type = int;
    static type id() { return 0; }
    static type op(const type &l, const type &r) { return l + r; }
};
