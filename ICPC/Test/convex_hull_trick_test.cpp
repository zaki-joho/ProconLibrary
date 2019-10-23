#include "../bits/stdc++.h"

using namespace std;

class LiChaoTree {
	using T = long long;
	using Line = pair<T, T>;
	const T inf = 1e9;
	// 最小化?
	bool isMinimum;
	int n;
	// 各区間には, その区間で最小(or最大)を取りうる直線を保持する
	vector<Line> node;
	vector<int> usd;

	static inline T f(const Line &line, T x) {return line.first * x + line.second;}

	// [l, r) に Line を追加, 現在ノードk
	void add(int k, int l, int r, Line line)
	{
		while(r-l>0)
		{
			if(!usd[k])
			{
				node[k] = line;
				usd[k] = true;
				return;
			}
			int m = (l + r) / 2;
			bool left = f(line, l) < f(node[k], l);
			bool mid = f(line, m) < f(node[k], m);
			bool right = f(line, r) < f(node[k], r);
			if(left && right)
			{
				node[k] = line;
				return;
			}
			if(!left && !right)
			{
				return;
			}
			if(mid)
			{
				swap(line, node[k]);
			}
			if(left != mid)
			{
				k = 2 * k + 1;
				r = m;
			}
			else
			{
				k = 2 * k + 1;
				l = m;
			}
		}
	}

public:
	// [0, n] 用の木を作る
	LiChaoTree(int _n, bool isMin=true) : isMinimum(isMin) {
		n = 1;
		while(n < _n) n *= 2;
		node.resize(2 * n - 1, Line(0, isMin ? inf : -inf));
		usd.resize(2 * n -1, false);
	}
	//　ax + b を追加する
	void add(T a, T b)
	{
		add(0, 0, n, Line(a, b));
		return;
	}
	T get(T x)
	{
		int k = x + (n - 1);
		T ret = usd[k] ? f(node[k], x) : inf;
		while(k > 0)
		{
			k = (k-1)/2;
			if(usd[k])
			{
				ret = min(ret, f(node[k], x));
			}
		}
		return ret;
	}
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
	vector<LiChaoTree> cht(TMAX + 1, LiChaoTree(4000));
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
