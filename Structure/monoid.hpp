#include "../bits/stdc++.h"
// SegmentTree に載せるモノイド
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

struct RangeSumQuery
{
    using type = int;
    static type id() { return 0; }
    static type op(const type &l, const type &r) { return l + r; }
};

// LazySegmentTree に載せるモノイド(未実装)
// http://kazuma8128.hatenablog.com/entry/2017/12/29/081929
/**
 * テンプレート
 * 操作1: 区間に対し, 含まれる全ての値をある演算で連結 (e.g. min, sum...)
 * 操作2: 区間に対し, 含まれる全ての値をある値と作用させ置換 (e.g. update, add)
struct QueryName
{
    using t1 = (保持データ, 操作1 の型);
    using t2 = (操作2 で作用させる値の型);
    static t1 id1() { t1 の単位元; }
    static t2 id2() { t2 の単位元; }
    static t1 op1(const t1 &l, const t1 &r) { return (型1同士の連結に用いる演算)(l, r); }
    static t1 op2(const t1 &l, const t2 &r) { return (操作2 で型2 を作用させる演算)(l, r); }
    static t2 op3(const t2 &l, const t2 &r) { return (型2 同士の演算); }
};
 */
struct RangeAddRangeSum
{
    using t1 = long long;
    using t2 = long long;
    static t1 id1() { return 0; }
    static t2 id2() { return 0; }
    static t1 op1(const t1 &l, const t1 &r) { return l + r; }
    static t1 op2(const t1 &l, const t2 &r) { return l + r; }
    static t2 op3(const t2 &l, const t2 &r) { return l + r; }
};
/*
struct RamgeUpdateRangeMinimum
{
    using t1 = int;
    using t2 = int;
    static t1 id1() { return INT_MAX; }
    static t2 id2() { return -1; }
    static t1 op1(const t1 &l, const t1 &r) { return std::min(l, r); }
    static t1 op2(const t1 &l, const t2 &r) { return r != id2() ? r : l; }
    static t2 op3(const t2 &l, const t2 &r) { return r != id2() ? r : l; }
};
*/