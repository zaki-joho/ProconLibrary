#include<vector>

using cost_t=int;
struct Edge {
    int from, to, cost;
    Edge(int from, int to, cost_t cost) : from(from), to(to), cost(cost) {}
};

using Edges = std::vector<Edge>;
using Graph = std::vector<Edges>;
