#include "../bits/stdc++.h"
constexpr int MOD = 1e9 + 7;

// a^b O(log b)
template<typename T>
T mypow(T a, T b) {
    if (b == 0)
        return 1;
    T tmp = mypow(a, b / 2);
    if (b % 2)
        return (((tmp * tmp) % MOD) * a) % MOD;
    else
        return (tmp * tmp) % MOD;
}
