#include "../bits/stdc++.h"

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

using ld = long double;
using Point = std::complex<ld>;

const ld eps = 1e-9, pi = acos(-1.0);

namespace std
{
bool operator<(const Point &lhs, const Point &rhs)
{
    if (lhs.real() < rhs.real() - eps)
        return true;
    if (lhs.real() > rhs.real() + eps)
        return false;
    return lhs.imag() < rhs.imag();
}
} // namespace std

Point input_point()
{
    ld x, y;
    std::cin >> x >> y;
    return Point(x, y);
}

bool eq(ld a, ld b)
{
    return (abs(a - b) < eps);
}

ld dot(Point a, Point b)
{
    return real(conj(a) * b);
}

ld cross(Point a, Point b)
{
    return imag(conj(a) * b);
}

// CCW::counter clockwise
int ccw(Point a, Point b, Point c)
{
    b -= a;
    c -= a;
    if (cross(b, c) > eps)
        return 1; // a,b,c : counter-clockwise
    if (cross(b, c) < -eps)
        return -1; // a,b,c : clockwise
    if (dot(b, c) < 0)
        return 2; // c,a,b : on a line
    if (norm(b) < norm(c))
        return -2; // a,b,c : on a line
    return 0;      // a,c,b : on a line
}

class Line
{
public:
    Point a, b;
    Line() : a(Point(0, 0)), b(Point(0, 0)) {}
    Line(Point a, Point b) : a(a), b(b) {}
};

ld dot(Line l, Line m)
{
    return dot((l.a - l.b), (m.a - m.b));
}

class Circle
{
public:
    Point p;
    ld r;
    Circle() : p(Point(0, 0)), r(0) {}
    Circle(Point p, ld r) : p(p), r(r) {}
};

// l:line, m:line が交点を持つか
bool isis_ll(Line l, Line m)
{
    return !eq(cross(l.b - l.a, m.b - m.a), 0);
}

// l:line, s:segment
bool isis_ls(Line l, Line s)
{
    return isis_ll(l, s) &&
           (cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < eps);
}

// s:segment, t:segment
bool isis_ss(Line s, Line t)
{
    return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
           ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

// p が l:line 上に存在するか
bool isis_lp(Line l, Point p)
{
    return (abs(cross(l.b - p, l.a - p)) < eps);
}

bool isis_sp(Line s, Point p)
{
    return (abs(s.a - p) + abs(s.b - p) - abs(s.b - s.a) < eps);
}

// p から l に下ろした足との交点
Point proj(Line l, Point p)
{
    ld t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
    return l.a + t * (l.a - l.b);
}

// l:line, t:line の交点
Point is_ll(Line l, Line m)
{
    Point lv = l.b - l.a, mv = m.b - m.a;
    assert(cross(lv, mv) != 0);
    return l.a + lv * cross(mv, m.a - l.a) / cross(mv, lv);
}

// p, l:line の距離
ld dist_lp(Line l, Point p)
{
    return abs(p - proj(l, p));
}

ld dist_ll(Line l, Line m)
{
    return isis_ll(l, m) ? 0 : dist_lp(l, m.a);
}

ld dist_ls(Line l, Line s)
{
    return isis_ls(l, s) ? 0 : std::min(dist_lp(l, s.a), dist_lp(l, s.b));
}

ld dist_sp(Line s, Point p)
{
    Point r = proj(s, p);
    return isis_sp(s, r) ? abs(r - p) : std::min(abs(s.a - p), abs(s.b - p));
}

ld dist_ss(Line s, Line t)
{
    if (isis_ss(s, t))
        return 0;
    return std::min({dist_sp(s, t.a), dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});
}

// a, b の垂直二等分線. a -> b を90度反時計回り回転
Line bisector(Point a, Point b)
{
    Point mid = (a + b) * Point(0.5, 0);
    return Line(mid, mid + (b - a) * Point(0, pi / 2));
}

// 直線 l, m のなす角を求める
ld degree_ll(Line l, Line m)
{
    ld cos_shita = dot(l, m) / (abs(l.b - l.a) * abs(m.b - m.a));
    if (cos_shita < -1.0)
        cos_shita = -1.0;
    if (cos_shita > 1.0)
        cos_shita = 1.0;
    ld shita = acos(cos_shita);
    // shita = sita * 180.0 / PI;
    return shita;
}

// c1, c2 の交点
std::vector<Point> is_cc(Circle c1, Circle c2)
{
    std::vector<Point> res;
    ld d = abs(c1.p - c2.p);
    ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
    ld dfr = c1.r * c1.r - rc * rc;
    if (abs(dfr) < eps)
        dfr = 0.0;
    else if (dfr < 0.0)
        return res; // no intersection
    ld rs = sqrt(dfr);
    Point diff = (c2.p - c1.p) / d;
    res.emplace_back(c1.p + diff * Point(rc, rs));
    if (dfr != 0.0)
        res.emplace_back(c1.p + diff * Point(rc, -rs));
    return res;
}

std::vector<Point> is_lc(Circle c, Line l)
{
    std::vector<Point> res;
    ld d = dist_lp(l, c.p);
    if (d < c.r + eps)
    {
        ld len = (d > c.r) ? 0.0 : sqrt(c.r * c.r - d * d); //safety;
        Point nor = (l.a - l.b) / abs(l.a - l.b);
        res.emplace_back(proj(l, c.p) + len * nor);
        res.emplace_back(proj(l, c.p) - len * nor);
    }
    return res;
}

std::vector<Point> is_sc(Circle c, Line l)
{
    std::vector<Point> v = is_lc(c, l), res;
    for (Point p : v)
        if (isis_sp(l, p))
            res.emplace_back(p);
    return res;
}

// p から c への接線
std::vector<Line> tangent_cp(Circle c, Point p)
{
    std::vector<Line> ret;
    Point v = c.p - p;
    ld d = abs(v);
    ld l = sqrt(norm(v) - c.r * c.r);
    if (std::isnan(l))
    {
        return ret;
    }
    Point v1 = v * Point(l / d, c.r / d);
    Point v2 = v * Point(l / d, -c.r / d);
    ret.emplace_back(Line(p, p + v1));
    if (l < eps)
        return ret;
    ret.emplace_back(Line(p, p + v2));
    return ret;
}

// c1, c2 の共通接線
std::vector<Line> tangent_cc(Circle c1, Circle c2)
{
    std::vector<Line> ret;
    if (abs(c1.p - c2.p) - (c1.r + c2.r) > -eps)
    {
        Point center = (c1.p * c2.r + c2.p * c1.r) / (c1.r + c2.r);
        ret = tangent_cp(c1, center);
    }
    if (abs(c1.r - c2.r) > eps)
    {
        Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);
        std::vector<Line> nret = tangent_cp(c1, out);
        ret.insert(ret.end(), nret.begin(), nret.end());
    }
    else
    {
        Point v = c2.p - c1.p;
        v /= abs(v);
        Point q1 = c1.p + v * Point(0, 1) * c1.r;
        Point q2 = c1.p + v * Point(0, -1) * c1.r;
        ret.emplace_back(Line(q1, q1 + v));
        ret.emplace_back(Line(q2, q2 + v));
    }
    return ret;
}

using Polygon = std::vector<Point>;

ld area(const Polygon &p)
{
    ld res = 0;
    int n = p.size();
    for (int i = 0; i < n; i++)
    {
        res += cross(p[i], p[(i + 1) % n]);
    }
    return res / 2;
}

bool is_counter_clockwise(const Polygon &poly)
{
    ld angle = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
    {
        Point a = poly[i], b = poly[(i + 1) % n], c = poly[(i + 2) % n];
        angle += arg((c - b) / (b - a));
    }
    return angle > eps;
}

// 0 => out
// 1 => on
// 2 => in
int is_in_polygon(const Polygon &poly, Point p)
{
    ld angle = 0;
    int n = poly.size();
    for (int i = 0; i < n; i++)
    {
        Point a = poly[i], b = poly[(i + 1) % n];
        if (isis_sp(Line(a, b), p))
            return 1;
        angle += arg((b - p) / (a - p));
    }
    return eq(angle, 0) ? 0 : 2;
}

// 凸包
Polygon convex_hull(std::vector<Point> ps)
{
    int n = ps.size();
    int k = 0;
    sort(ps.begin(), ps.end());
    Polygon ch(2 * n);
    for (int i = 0; i < n; ch[k++] = ps[i++])
        while (k >= 2 && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0)
            --k;
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = ps[i--])
        while (k >= t && ccw(ch[k - 2], ch[k - 1], ps[i]) <= 0)
            --k;
    ch.resize(k - 1);
    return ch;
}

// 凸包カット
Polygon convex_cut(const Polygon &ps, Line l)
{
    int n = ps.size();
    Polygon Q;
    for (int i = 0; i < n; i++)
    {
        Point A = ps[i], B = ps[(i + 1) % n];
        Line m = Line(A, B);
        if (ccw(l.a, l.b, A) != -1)
            Q.emplace_back(A);
        if (ccw(l.a, l.b, A) * ccw(l.a, l.b, B) < 0 && isis_ll(l, m))
            Q.emplace_back(is_ll(l, m));
    }
    return Q;
}

void add_point(std::vector<Point> &ps, Point p)
{
    for (Point q : ps)
        if (abs(q - p) < eps)
            return;
    ps.emplace_back(p);
}

// Voronoi 図: http://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=3668810
// polygon を ps でボロノイ分割する時の ps[index] に割り当てられる多角形
Polygon voronoi(const Polygon &polygon, const std::vector<Point> &ps, int index)
{
    Polygon p = polygon;
    int n = ps.size();
    for (int j = 0; j < n; j++)
    {
        if (index == j)
            continue;
        Line l = bisector(ps[index], ps[j]);
        p = convex_cut(p, l);
    }
    return p;
}

// 凸多角形の直径（最遠点対）, インデックスのペアを返す, O(n)
ld convexDiameter(const Polygon &ps)
{
    int n = ps.size();
    int i = min_element(ps.begin(), ps.end()) - ps.begin();
    int j = max_element(ps.begin(), ps.end()) - ps.begin();
    int reti = i, retj = j;
    ld d = 0;
    for (int k = 0; k < 2 * n; k++)
    {
        if (d < norm(ps[i] - ps[j]))
        {
            d = norm(ps[i] - ps[j]);
            reti = i;
            retj = j;
        }
        if (cross(ps[i] - ps[(i + 1) % n], ps[(j + 1) % n] - ps[j]) <= 0)
            j = (j + 1) % n;
        else
            i = (i + 1) % n;
    }
    return d;
    // return std::make_pair(reti, retj);
}

// 多角形の幾何学的重心
Point centroid(const Polygon &ps)
{
    int n = ps.size();
    ld sum = 0;
    Point c;
    for (int i = 0; i < n; i++)
    {
        ld a = cross(ps[i], ps[(i + 1) % n]);
        sum += a;
        c += (ps[i] + ps[(i + 1) % n]) * a;
    }
    return 1.0 / sum / 3 * c;
}

bool compareY(Point a, Point b)
{
    return a.imag() < b.imag();
}

ld closestPair(Point *a, int n) // a is sorted
{
    static const ld inf = 1e15;
    if (n <= 1)
        return inf;
    int m = n / 2;
    ld x = a[m].real();
    ld d = std::min(closestPair(a, m), closestPair(a + m, n - m));
    std::inplace_merge(a, a + m, a + n, compareY);
    // a は y の昇順

    std::vector<Point> b;
    for (int i = 0; i < n; i++)
    {
        if (fabs(a[i].real() - x) >= d)
            continue;

        for (int j = 0; j < int(b.size()); j++)
        {
            ld dx = a[i].real() - b[int(b.size()) - j - 1].real();
            ld dy = a[i].imag() - b[int(b.size()) - j - 1].imag();
            if (dy >= d)
                break;
            d = std::min(d, sqrt(dx * dx + dy * dy));
        }
        b.push_back(a[i]);
    }
    return d;
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
