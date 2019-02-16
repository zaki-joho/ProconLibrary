#include "../bits/stdc++.h"
/**
 * 列 a に対し, 区間の両端が単調非減少のとき,
 * 区間min クエリに線形で答えが求まる, ウィンドウサイズは固定
 */
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3385735
template <typename T>
class SlideMinimum
{
    // (位置, 値)
    std::deque<std::pair<int, T>> deq;
    int pos, window;

  public:
    SlideMinimum(int _w) : pos(0), window(_w) {}
    T query(T val)
    {
        while (!deq.empty() && deq.front().first <= pos - window)
            deq.pop_front();
        while (!deq.empty() && deq.back().second >= val)
            deq.pop_back();
        deq.push_back(std::make_pair(pos++, val));
        return deq.front().second;
    }
};
