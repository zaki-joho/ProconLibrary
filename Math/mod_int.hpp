#include "../bits/stdc++.h"
// 自動Mod
// verified: https://atcoder.jp/contests/arc033/submissions/4271515
template <int Mod>
struct ModInt
{
    using type = long long;
    type val;
    ModInt() : val(0) {}
    ModInt(int _v) : val(_v)
    {
        if (val >= Mod)
            val %= Mod;
        else if (val < 0)
            val = (val % Mod + Mod) % Mod;
    }

    bool operator==(const ModInt &a) const { return val == a.val; }
    ModInt &operator+=(const ModInt &a)
    {
        val += a.val;
        if (val >= Mod)
            val -= Mod;
        return *this;
    }
    ModInt &operator-=(const ModInt &a)
    {
        val -= a.val;
        if (val < 0)
            val += Mod;
        return *this;
    }
    ModInt &operator*=(const ModInt &a)
    {
        val *= a.val;
        val %= Mod;
        return *this;
    }
    ModInt &operator/=(ModInt &a)
    {
        val *= a.inv();
        return *this;
    }

    ModInt operator+(const ModInt &a) const
    {
        ModInt ret = *this;
        return ret += a;
    }
    ModInt operator-(ModInt &a) const
    {
        ModInt ret = *this;
        return ret -= a;
    }
    ModInt operator-() const { return ModInt(0) - *this; }
    ModInt operator*(const ModInt &a) const
    {
        ModInt ret = *this;
        return ret *= a;
    }
    ModInt operator/(ModInt &a)
    {
        return ModInt(*this) /= a;
    }

    ModInt inv() const
    {
        type a = val, b = Mod, u = 1, v = 0;
        while (b > 0)
        {
            type t = a / b;
            a -= t * b;
            std::swap(a, b);
            u -= t * v;
            std::swap(u, v);
        }
        return ModInt(u);
    }
};

template <int Mod>
std::istream &operator>>(std::istream &is, ModInt<Mod> &val)
{
    long long x;
    is >> x;
    val = x;
    return is;
}

template <int Mod>
std::ostream &operator<<(std::ostream &os, ModInt<Mod> &val)
{
    os << val.val;
    return os;
}

template <int Mod>
ModInt<Mod> ModPow(ModInt<Mod> a, ModInt<Mod> n)
{
    ModInt<Mod> ret(1);
    while (n.val)
    {
        if (n.val & 1)
            ret *= a;
        a *= a;
        n.val >>= 1;
    }
    return ret;
}
