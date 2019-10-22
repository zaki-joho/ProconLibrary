#include "polygon.hpp"

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

// 凸多角形の直径（最遠点対）, O(n)
ld convexDiameter(const Polygon &ps)
{
    int n = ps.size();
    int i = min_element(ps.begin(), ps.end()) - ps.begin();
    int j = max_element(ps.begin(), ps.end()) - ps.begin();
    // int reti = i, retj = j;
    ld d = 0;
    for (int k = 0; k < 2 * n; k++)
    {
        if (d < norm(ps[i] - ps[j]))
        {
            d = norm(ps[i] - ps[j]);
            // reti = i;
            // retj = j;
        }
        if (cross(ps[i] - ps[(i + 1) % n], ps[(j + 1) % n] - ps[j]) <= 0)
            j = (j + 1) % n;
        else
            i = (i + 1) % n;
    }
    return d;
    // return std::make_pair(reti, retj);
}

// 多角形の幾何学的重心 unverified
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

ld closestPair(Point *a, int n)
{
    if (n <= 1)
        return -1;
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
            d = std::min(d, (ld)sqrt(dx * dx + dy * dy));
        }
        b.push_back(a[i]);
    }
    return d;
}
