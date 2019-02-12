const int MOD = 1e9 + 7;

// a^b O(log b)
template<typename T>
T mypow(T a, T b)
{
    if (b == 0)
        return 1;
    T tmp = mypow(a, b / 2);
    if (b % 2)
        return (((tmp * tmp) % MOD) * a) % MOD;
    else
        return (tmp * tmp) % MOD;
}

// nCk O(n + klogMOD)
template<typename T>
T comb(T n, T k)
{
    T res = 1;
    k = min(n - k, k);
    for (T i = n - k + 1; i <= n; i++)
        res = (res * i) % MOD;
    for (T i = 1; i <= k; i++)
        res = (res * mypow<T>(i, MOD - 2)) % MOD;
    return res;
}

// nHk = n+k-1 C k
template<typename T>
T H(T n, T k)
{
    return comb(n + k - 1, k);
}

// v[i][j] := iCj
template<typename T>
vector<vector<T>> comb2(T n, T r)
{
    vector<vector<T>> v(n + 1, vector<T>(n + 1, 0));
    for (int i = 0; i < v.size(); i++)
    {
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for (int j = 1; j < v.size(); j++)
    {
        for (int k = 1; k < j; k++)
        {
            v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
            v[j][k] %= MOD;
        }
    }
    return v;
}
