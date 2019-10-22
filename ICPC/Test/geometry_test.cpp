#include "../Geometry/utils.hpp"

using namespace std;

template <typename T>
void printv(const vector<T> &v)
{
    int sz = v.size();
    for (int i = 0; i < sz; i++)
    {
        cout << v[i] << " \n"[i == sz - 1];
    }
}

void solve_cgl_1_a()
{
    auto p1 = input_point(), p2 = input_point();
    int q;
    cin >> q;
    while (q--)
    {
        auto p = input_point();
        auto ret = proj(Line(p1, p2), p);
        cout << fixed << setprecision(10) << ret.real() << " " << ret.imag() << endl;
    }
}

void solve_cgl_1_b()
{
    auto p1 = input_point(), p2 = input_point();
    int q;
    cin >> q;
    while (q--)
    {
        auto p = input_point();
        auto ret = proj(Line(p1, p2), p);
        cout << fixed << setprecision(10) << 2 * ret.real() - p.real() << " " << 2 * ret.imag() - p.imag() << endl;
    }
}

void solve_cgl_1_c()
{
    auto p0 = input_point(), p1 = input_point();
    int q;
    cin >> q;
    while (q--)
    {
        auto p2 = input_point();
        int ret = ccw(p0, p1, p2);
        if (ret == 1)
            cout << "COUNTER_CLOCKWISE" << endl;
        else if (ret == -1)
            cout << "CLOCKWISE" << endl;
        else if (ret == 2)
            cout << "ONLINE_BACK" << endl;
        else if (ret == -2)
            cout << "ONLINE_FRONT" << endl;
        else
            cout << "ON_SEGMENT" << endl;
    }
}

void solve_cgl_2_a()
{
    int q;
    cin >> q;
    while (q--)
    {
        auto p0 = input_point(), p1 = input_point(), p2 = input_point(), p3 = input_point();
        Line l(p0, p1), m(p2, p3);
        if (!isis_ll(l, m))
        {
            cout << 2 << endl;
        }
        else if (eq(dot(l.b - l.a, m.b - m.a), 0))
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
}

void solve_cgl_2_b()
{
    int q;
    cin >> q;
    while (q--)
    {
        auto p0 = input_point(), p1 = input_point(), p2 = input_point(), p3 = input_point();
        Line s1(p0, p1), s2(p2, p3);
        cout << (isis_ss(s1, s2) ? 1 : 0) << endl;
    }
}

void solve_cgl_2_c()
{
    int q;
    cin >> q;
    while (q--)
    {
        auto p0 = input_point(), p1 = input_point(), p2 = input_point(), p3 = input_point();
        Line s1(p0, p1), s2(p2, p3);
        auto ret = is_ll(s1, s2);
        cout << fixed << setprecision(10) << ret.real() << " " << ret.imag() << endl;
    }
}

void solve_cgl_2_d()
{
    int q;
    cin >> q;
    while (q--)
    {
        auto p0 = input_point(), p1 = input_point(), p2 = input_point(), p3 = input_point();
        Line s1(p0, p1), s2(p2, p3);
        cout << fixed << setprecision(10) << dist_ss(s1, s2) << endl;
    }
}

void solve_cgl_3_a()
{
    Polygon p;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        p.push_back(input_point());
    }
    cout << fixed << setprecision(10) << area(p) << endl;
}

void solve_cgl_3_b()
{
    Polygon p;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        p.push_back(input_point());
    }
    auto cv = convex_hull(p);
    cout << (eq(area(p), area(cv)) ? 1 : 0) << endl;
}

void solve_cgl_3_c()
{
    Polygon ps;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        ps.push_back(input_point());
    }
    int q;
    cin >> q;
    while (q--)
    {
        auto p = input_point();
        int ret = is_in_polygon(ps, p);
        cout << ret << endl;
    }
}

// AOJと凸包の仕様が少し違う(辺上の点を含めない)ので略…
void solve_cgl_4_a()
{
    int n;
    cin >> n;
    Polygon ps;
    for (int i = 0; i < n; i++)
    {
        ps.push_back(input_point());
    }
    auto ret = convex_hull(ps);
    cout << ret.size() << endl;
    for (auto p : ret)
    {
        cout << (int)p.real() << " " << (int)p.imag() << endl;
    }
}

void solve_cgl_4_b()
{
    int n;
    cin >> n;
    Polygon ps;
    for (int i = 0; i < n; i++)
    {
        ps.push_back(input_point());
    }
    auto ret = convexDiameter(ps);
    cout << fixed << setprecision(10) << sqrt(ret) << endl;
}

// AOJと凸包の仕様が少し違う(辺上の点を含めない)ので略…
void solve_cgl_4_c()
{
    int n;
    cin >> n;
    Polygon ps;
    for (int i = 0; i < n; i++)
    {
        ps.push_back(input_point());
    }
    int q;
    cin >> q;
    while (q--)
    {
        auto p0 = input_point(), p1 = input_point();
        auto l = Line(p0, p1);
        auto ret = convex_cut(ps, l);
        cout << fixed << setprecision(10) << area(ret) << endl;
    }
}

const int MAX_N = 100000;
Point a[MAX_N];

void solve_cgl_5_a()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        auto p = input_point();
        a[i] = p;
    }
    sort(a, a + n);
    auto ret = closestPair(a, n);
    cout << fixed << setprecision(10) << ret << endl;
}

// cgl_6_a: 線分交差

void solve_cgl_7_a()
{
    auto p0 = input_point();
    ld r0, r1;
    cin >> r0;
    auto p1 = input_point();
    cin >> r1;
    Circle c0(p0, r0), c1(p1, r1);
    auto ls = tangent_cc(c0, c1);
    cout << ls.size() << endl;
}

void solve_cgl_7_d()
{
    auto p = input_point();
    ld r;
    cin >> r;
    Circle c(p, r);
    int q;
    cin >> q;
    cout << fixed << setprecision(10);
    while (q--)
    {
        auto p0 = input_point(), p1 = input_point();
        Line l(p0, p1);
        auto ret = is_lc(c, l);
        assert(ret.size() <= 2);
        sort(ret.begin(), ret.end());
        cout << ret[0].real() << " " << ret[0].imag();
        if (ret.size() == 2)
        {
            cout << " " << ret[1].real() << " " << ret[1].imag();
        }
        cout << endl;
    }
}

void solve_cgl_7_e()
{
    auto p0 = input_point();
    ld r0, r1;
    cin >> r0;
    auto p1 = input_point();
    cin >> r1;
    Circle c0(p0, r0), c1(p1, r1);
    auto ret = is_cc(c0, c1);
    if ((int)ret.size() == 1)
        ret.push_back(ret[0]);
    sort(ret.begin(), ret.end());
    cout << fixed << setprecision(10);
    cout << ret[0].real() << " " << ret[0].imag() << " " << ret[1].real() << " " << ret[1].imag() << endl;
}

void solve_cgl_7_f()
{
    auto p = input_point();
    auto p0 = input_point();
    ld r0;
    cin >> r0;
    Circle c(p0, r0);
    auto ls = tangent_cp(c, p);
    vector<Point> ret;
    for (auto l : ls)
    {
        auto ps = is_lc(c, l);
        //assert((int)ps.size() == 1);
        ret.push_back(ps[0]);
    }
    sort(ret.begin(), ret.end());
    cout << fixed << setprecision(10);
    cout << ret[0].real() << " " << ret[0].imag() << " " << ret[1].real() << " " << ret[1].imag() << endl;
}

void solve_cgl_7_g()
{
    ld r0, r1;
    auto p0 = input_point();
    cin >> r0;
    auto p1 = input_point();
    cin >> r1;
    Circle c0(p0, r0), c1(p1, r1);
    auto ls = tangent_cc(c0, c1);
    vector<Point> ret;
    for (auto l : ls)
    {
        auto ps = is_sc(c0, l);
        //assert((int)ps.size() == 1);
        ret.push_back(ps[0]);
    }
    sort(ret.begin(), ret.end());
    for (auto p : ret)
    {
        cout << fixed << setprecision(10) << p.real() << " " << p.imag() << endl;
    }
}

// cgl_7_h: 円と多角形の共通部分(は?)
// 参考実装: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=2114290

int main()
{
    cin.tie(0);
    ios::sync_with_stdio(false);
}
