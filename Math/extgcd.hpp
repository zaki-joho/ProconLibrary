// gcd(a, b)
template<typename T>
T gcd(T a, T b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// ax+by=gcd(x,y)となるx,yを求める
// 返り値は gcd(a,b)
// verified: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3386893
template<typename T>
T extgcd(T a, T b, T &x, T &y)
{
    T d = a;
    if (b != 0)
    {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else
    {
        x = 1;
        y = 0;
    }
    return d;
}
