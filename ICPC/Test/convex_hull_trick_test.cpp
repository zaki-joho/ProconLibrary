#include "../bits/stdc++.h"

using namespace std;

// https://github.com/satanic0258/Cpp_snippet/blob/master/src/technique/ConvexHullTrick.cpp
using CHT_TYPE = long long;
class ConvexHullTrickDynamic
{
private:
	// 直線 **************************************************************
	struct Line
	{
		CHT_TYPE a, b;								  // y = ax + b
		mutable std::function<const Line *()> getSuc; // 次の直線へのポインタ (ソートで用いる)

		bool operator<(const Line &rhs) const
		{
			// 取得クエリでは次の直線との差分でソート
			if (rhs.b == IS_QUERY)
			{
				const Line *suc = getSuc();
				if (suc == nullptr)
					return false;
				const CHT_TYPE &x = rhs.a;
				return (suc->a - a) * x + suc->b - b > 0;
			}
			if (b == IS_QUERY)
			{
				const Line *suc = rhs.getSuc();
				if (suc == nullptr)
					return true;
				const CHT_TYPE &x = a;
				return (suc->a - rhs.a) * x + suc->b - rhs.b < 0;
			}

			// 通常の直線どうしは傾きソート
			return a < rhs.a;
		}
	};

	// 直線集合 **********************************************************
	class LinesSet : public std::multiset<Line>
	{
	private:
		// true -> 最小値クエリ, false -> 最大値クエリ
		bool flagMin;

	public:
		// コンストラクタ ( 第一引数falseで最大値クエリ,デフォルトで最小値クエリ )
		LinesSet(bool flagMin = false) : flagMin(flagMin){};

		// 直線lが不必要であるかどうか
		inline bool isBad(iterator l)
		{
			const auto &&nel = std::next(l);
			if (l == begin())
			{ // lが傾き最小のとき
				if (nel == end())
					return false; // lしかないなら必要
				return l->a == nel->a && l->b <= nel->b;
			}
			else
			{
				const auto &&prl = std::prev(l);
				if (nel == end())
					return l->a == prl->a && l->b <= prl->b;
				return (prl->b - l->b) * (nel->a - l->a) >= (nel->b - l->b) * (prl->a - l->a);
			}
		}

		// 直線y=ax+bを追加する
		inline void add(CHT_TYPE a, CHT_TYPE b)
		{
			if (flagMin)
				a = -a, b = -b;
			auto &&it = insert({a, b});
			it->getSuc = [=] { return (std::next(it) == end() ? nullptr : &*std::next(it)); };
			if (isBad(it))
			{
				erase(it);
				return;
			}
			while (std::next(it) != end() && isBad(std::next(it)))
				erase(std::next(it));
			while (it != begin() && isBad(std::prev(it)))
				erase(std::prev(it));
		}

		// 直線群の中でxの時に最小(最大)となる値を返す
		inline CHT_TYPE get(CHT_TYPE x)
		{
			auto &&l = *lower_bound(Line{x, IS_QUERY});
			if (flagMin)
				return -l.a * x - l.b;
			else
				return l.a * x + l.b;
		}
	};

	static const CHT_TYPE IS_QUERY = std::numeric_limits<CHT_TYPE>::lowest();
	LinesSet linesSet;

public:
	// コンストラクタ ( 第一引数falseで最大値クエリ,デフォルトで最小値クエリ )
	ConvexHullTrickDynamic(bool flagMin = false) : linesSet(flagMin) {
		linesSet.add(0, -1e15);
	}
	// 直線y=ax+bを追加する
	inline void add(CHT_TYPE a, CHT_TYPE b) { linesSet.add(a, b); }
	// あるxのときの直線集合での最小値を求める
	inline CHT_TYPE get(CHT_TYPE x) { return linesSet.get(x); }
};

// http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3947471
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
	vector<ConvexHullTrickDynamic> cht(TMAX + 1);
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
