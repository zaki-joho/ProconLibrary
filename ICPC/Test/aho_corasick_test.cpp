#include "bits/stdc++.h"

#define REP(i, n) for (int i = 0; i < n; ++i)
// https://onlinejudge.u-aizu.ac.jp/status/users/EtoNagisa/submissions/1/2212/judge/3966278/C++14
using namespace std;

#include "bits/stdc++.h"
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
		return c - 'A';
	}
	static char invert(int i) {
		return i + 'A';
	}
};

template <typename Char> struct AhoCorasick {
	static constexpr int invalid = -1;

	struct PMA {
		int fail;
		vector<int> next, accept;

		PMA() : fail(invalid), next(Char::size, invalid) {}
	};

	const int K;
	vector<unique_ptr<PMA>> nodes;

	int next(int index, char cc) {
		int c = Char::convert(cc);
		int now = index;
		while (nodes[now]->next[c] == invalid && now != 0) {
			now = nodes[now]->fail;
		}
		now = nodes[now]->next[c];
		if (now == invalid) now = 0;
		return now;
	}

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
					int nxt = next(nodes[now]->fail, Char::invert(c));
					nodes[nodes[now]->next[c]]->fail = nxt;
					for (auto ac : nodes[nxt]->accept) {
						nodes[nodes[now]->next[c]]->accept.push_back(ac);
					}
				}
			}
		}
		for (int c = 0; c < Char::size; c++) {
			if (nodes[root]->next[c] != invalid) {
				que.push(nodes[root]->next[c]);
			} else {
				nodes[root]->next[c] = root;
			}
		}
		while (!que.empty()) {
			int p = que.front();
			que.pop();

			for (int c = 0; c < Char::size; c++) {
				if (nodes[p]->next[c] == invalid) {
					int nxt = nodes[nodes[p]->fail]->next[c];
					assert(nxt != invalid);
					nodes[p]->next[c] = nxt;
				} else {
					que.push(nodes[p]->next[c]);
				}
			}
		}
	}
	vector<vector<int>> match(const string &str) {
		vector<vector<int>> ret(K);
		int now = 0;
		for (int i = 0; i < (int)str.size(); i++) {
			now = next(now, str[i]);
			for (auto k : nodes[now]->accept) {
				ret[k].push_back(i);
			}
		}
		return ret;
	}
};

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
string mv = "DRUL";
int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m, n) {
		vector<string> v(n);
		REP(i, n) cin >> v[i];
		int qu;
		cin >> qu;
		vector<string> p(qu);
		REP(i, qu) cin >> p[i];
		AhoCorasick<characters> ac(p);
		int sx = -1, sy = -1, tx = -1, ty = -1;
		REP(i, n) REP(j, m) {
			if (v[i][j] == 'S') {
				sx = i;
				sy = j;
			} else if (v[i][j] == 'G') {
				tx = i;
				ty = j;
			}
		}
		int k = ac.nodes.size();
		vector<vector<vector<int>>> dp(
		    n, vector<vector<int>>(m, vector<int>(k, 1e9)));
		dp[sx][sy][0] = 0;
		queue<pair<pair<int, int>, int>> q;
		q.push({{sx, sy}, 0});
		while (!q.empty()) {
			auto c = q.front();
			q.pop();
			int x = c.first.first, y = c.first.second, s = c.second;
			REP(d, 4) {
				int nx = x + dx[d], ny = y + dy[d], ns = ac.next(s, mv[d]);
				if (nx < 0 || nx >= n || ny < 0 || ny >= m ||
				    v[nx][ny] == '#' || ac.nodes[ns]->accept.size() > 0)
					continue;
				if (dp[nx][ny][ns] > dp[x][y][s] + 1) {
					dp[nx][ny][ns] = dp[x][y][s] + 1;
					q.push({{nx, ny}, ns});
				}
			}
		}
		int ans = 1e9;
		REP(i, k) ans = min(ans, dp[tx][ty][i]);
		if (ans == 1e9)
			cout << -1 << endl;
		else
			cout << ans << endl;
	}
}
