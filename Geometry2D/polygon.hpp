#include "geometry.hpp"
#include "line.hpp"

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

// -1 => out
//  0 => on
//  1 => in
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
Polygon voronoi(const Polygon &polygon, const vector<Point> &ps, int index)
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
