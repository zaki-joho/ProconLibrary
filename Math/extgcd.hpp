// ax+by=gcd(x,y)となるx,yを求める
// 返り値は gcd(a,b)
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
