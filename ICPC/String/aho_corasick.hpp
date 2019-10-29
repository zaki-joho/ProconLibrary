#include "../bits/stdc++.h"
using namespace std;
// 入力文字列に対してマッチするパターンを検索
// O(N + M)
// N := 入力文字列, M := パターン文字列の長さ合計
/*
1. パターンから Trie 木を作成.
2. 各ノードが表す文字列の末尾と一致するノードの内,
文字列長が最大のノードへ辺を張る. そのようなノードが存在しなければ根に辺を張る.
この処理は bfs で可能. 各ノードはその祖先が一致する文字列の情報も持つ.
3. PMA(パターンマッチングオートマトン)の完成！
*/

// 出現文字
struct characters {
  // lower alphabets
  static int const size = 26;
  static int convert(char c) {
    return c - 'a';
  }
  static char invert(int i) {
    return i + 'a';
  }
};

template <typename Char>
class AhoCorasick {
  static constexpr int invalid = -1;

  struct PMA {
    int fail;
    vector<int> next, accept;

    PMA() : fail(invalid), next(Char::size, invalid) {}
  };

  const int K;
  vector<unique_ptr<PMA>> nodes;

  int transition(int index, char cc) {
    int c = Char::convert(cc);
    int now = index;
    while (nodes[now]->next[c] == invalid && now != 0) {
      now = nodes[now]->fail;
    }
    now = nodes[now]->next[c];
    if (now == invalid) now = 0;
    return now;
  }

public:
  AhoCorasick(const vector<string> &ts) : K((int)ts.size()) {
    const int root = 0;
    // root node
    nodes.push_back(make_unique<PMA>());
    nodes[root]->fail = root;
    for (int i = 0; i < K; i++) {
      int now = root;
      for (auto cs : ts[i]) {
        int c = Char::convert(cs);
        if (nodes[now]->next[c] == invalid) {
          nodes[now]->next[c] = (int)nodes.size();
          nodes.push_back(make_unique<PMA>());
        }
        now = nodes[now]->next[c];
      }
      nodes[now]->accept.push_back(i);
    }

    queue<int> que;
    for (int c = 0; c < Char::size; c++) {
      if (nodes[root]->next[c] != invalid) {
        nodes[nodes[root]->next[c]]->fail = root;
        que.push(nodes[root]->next[c]);
      }
    }
    while (!que.empty()) {
      int now = que.front();
      que.pop();
      for (int c = 0; c < Char::size; c++) {
        if (nodes[now]->next[c] != invalid) {
          que.push(nodes[now]->next[c]);
          int nxt = transition(nodes[now]->fail, Char::invert(c));
          nodes[nodes[now]->next[c]]->fail = nxt;
          for (auto ac : nodes[nxt]->accept) {
            nodes[nodes[now]->next[c]]->accept.push_back(ac);
          }
        }
      }
    }
  }
  vector<vector<int>> match(const string &str) {
    vector<vector<int>> ret(K);
    int now = 0;
    for (int i = 0; i < (int)str.size(); i++) {
      now = transition(now, str[i]);
      for (auto k : nodes[now]->accept) {
        ret[k].push_back(i);
      }
    }
    return ret;
  }
};
