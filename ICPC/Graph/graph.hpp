#include "../bits/stdc++.h"

// グラフ基本要素
// For shortest_path, minimum_spanning_tree

struct Edge {
    int from, to, cost;
    Edge(int from, int to, int cost) : from(from), to(to), cost(cost) {}
};

using Edges = std::vector<Edge>;
using Graph = std::vector<Edges>;
using P = std::pair<int, int>;
constexpr int INF = 1e9;

// 逆順にしているので注意
bool operator<(const Edge &e, const Edge &f) {
    return e.cost > f.cost;
}
