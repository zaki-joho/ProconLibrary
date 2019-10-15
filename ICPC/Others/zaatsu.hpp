#include "../bits/stdc++.h"
template <typename T>
void coordinateCompression(std::vector<T> &a) {
    int N = a.size();
    std::vector<T> xs = a;
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    for (int i = 0; i < N; i++) {
        a[i] = lower_bound(xs.begin(), xs.end(), a[i]) - xs.begin();
    }
}
