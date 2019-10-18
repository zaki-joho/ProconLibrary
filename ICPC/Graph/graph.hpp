#include<bits/stdc++.h>
using namespace std;
using cost_t=int;

struct Edge {
    int from, to;
    cost_t cost;
    Edge(int from, int to, cost_t cost) : from(from), to(to), cost(cost) {}
};

using Edges = vector<Edge>;
using Graph = vector<Edges>;
