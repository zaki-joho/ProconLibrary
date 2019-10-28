#include "../bits/stdc++.h"

struct Trie {
  Trie *node[26];
  int val;
  Trie() {
    val = 0;
    std::fill(node, node + 26, (Trie *)0);
  }
  void insert(const std::string &s, int w) {
    Trie *r = this;
    for (int i = 0; i < (int)s.length(); i++) {
      int c = s[i] - 'a';
      if (!r->node[c]) r->node[c] = new Trie;
      r = r->node[c];
    }
    r->val = w;
    return;
  }
  Trie *find(const char &s, Trie *pos) {
    int c = s - 'a';
    if (!pos->node[c]) return (Trie *)0;
    return pos->node[c];
  }
};
