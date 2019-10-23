#include "../bits/stdc++.h"

using namespace std;

class LiChaoTree {
	LiChaoTree() {}
};

// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3946763
void solve_aoj_2725()
{
	using ll = long long;
	const ll inf = 1e15;
	int N, TMAX;
	cin >> N >> TMAX;
	struct Song
	{
		ll t, p, f;
	};
	vector<Song> songs;
	for (int i = 0; i < N; i++)
	{
		ll t, p, f;
		cin >> t >> p >> f;
		songs.push_back(Song{t, p, f});
	}
	sort(songs.begin(), songs.end(), [](const Song &e, const Song &f) { return e.f < f.f; });
	// dp[i][j] := i曲目まで歌って, 時間j 消費した
	vector<vector<ll>> dp(N + 1, vector<ll>(TMAX + 1, -inf));
	vector<LiChaoTree> cht(TMAX + 1);
	ll ret = 0;
	dp[0][0] = 0;
	for (int i = 0; i < N; i++)
	{
		// length, pleasure, feature
		ll t = songs[i].t, p = songs[i].p, f = songs[i].f;
		dp[i + 1][t] = p;
		for (int j = TMAX; j >= 0; j--)
		{
			if (j - t < 0)
				break;
			dp[i + 1][j] = max(dp[i + 1][j], cht[j - t].get(f) + p - f * f);
			if (dp[i + 1][j] != -inf)
			{
				cht[j].add(2 * f, dp[i + 1][j] - f * f);
			}
			ret = max(ret, dp[i + 1][j]);
		}
	}
	cout << ret << endl;
}

int main()
{
	solve_aoj_2725();
}
