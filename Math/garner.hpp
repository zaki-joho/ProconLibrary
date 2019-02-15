#include "../bits/stdc++.h"
/**
 * x mod m_0 == u_0
 * x mod m_1 == u_1
 * ...
 * x mod m_n == u_n
 * となるような x を中国剰余定理を用いて求める(m_i は互いに素)
 */
// O(N^2)
/*
using ll = long long;

int mod_inv(ll a, ll m)
{
    ll b = m, u = 1, v = 0;
    while (b > 0)
    {
        ll t = a / b;
        a -= t * b;
        std::swap(a, b);
        u -= t * v;
        std::swap(u, v);
    }
    return (u % m + m) % m;
}

ll garner(std::vector<ll> m, std::vector<ll> u, int mod)
{
    const int n = m.size();
    std::vector<ll> inv(n);
    for (int i = 1; i < n; i++)
    {
        ll p = m[0] % m[i];
        for (int j = 1; j < i; j++)
        {
            p = (p * m[j]) % m[i];
        }
        inv[i] = mod_inv(p, m[i]);
    }
    std::vector<ll> v(n);
    v[0] = u[0];
    for (int i = 1; i < n; i++)
    {
        ll tmp = v[i - 1];
        for (int j = i - 2; j >= 0; j--)
        {
            tmp = (tmp * m[j] + v[j]) % m[i];
        }
        v[i] = ((u[i] - tmp) * inv[i]) % m[i];
        if (v[i] < 0)
            v[i] += m[i];
    }
    ll res = v[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        res = (res * m[i] + v[i]) % mod;
    }
    return res;
}
*/