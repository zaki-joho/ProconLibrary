# ICPC Library

## Purpose

ここにチームライブラリを置く

## Index

- Geometry
    + geometry.hpp
    + intersect.hpp
    + convex.hpp
- Graph
    + graph.hpp
    + dijkstra.hpp
    + bellman_ford.hpp
    + spfa.hpp
    + scc.hpp
    + articulation_points.hpp
    + bridges.hpp
    + lca.hpp
    + ford_fullkerson.hpp
    + dinic.hpp
    + min_cost_flow.hpp
    + minimum_spanning_tree.hpp
    + maximum_independent_set.hpp
- Math
    + fft.cpp
    + matrix.hpp
    + crt.hpp
    + polynomial_lagrange.hpp
- String
    + z_algorithm.hpp
    + mp.hpp
    + aho_corasick.hpp
    + suffix_array.hpp
    + rolling_hash.hpp
- Structure
    + union_find.hpp
    + bit.hpp
    + segment_tree.hpp
    + lazy_segment_tree.hpp
    + trie.hpp
    + skew_heap.hpp
- Others
    + memo.txt
- pending
    + minimum_cut.hpp
    + heavy_light_decomposition.hpp
    + two_sat.hpp
    + slide_min.hpp

## Usage

1. ICPC/ 以下の対応する場所にソースコード書く
2. ICPC/Tex/src/ 以下の対応する .tex ファイルを更新する

```
platex main.tex
dvipdfmx main.dvi
```
で良い感じのpdf出てきたらok.
