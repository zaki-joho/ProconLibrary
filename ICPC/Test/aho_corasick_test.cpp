#include "bits/stdc++.h"

#define REP(i, n) for (int i = 0; i < n; ++i)
// https://onlinejudge.u-aizu.ac.jp/status/users/EtoNagisa/submissions/1/2212/judge/3966278/C++14
using namespace std;

#include "../String/aho_corasick.hpp"

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
				    v[nx][ny] == '#' || ac.nodes[ns].accept.size() > 0)
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
