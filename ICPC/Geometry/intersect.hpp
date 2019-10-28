#include "geometry.hpp"

// l:line, m:line が交点を持つか
bool isis_ll(Line l, Line m) { return !eq(cross(l.b - l.a, m.b - m.a), 0); }

// l:line, s:segment
bool isis_ls(Line l, Line s) {
  return isis_ll(l, s) &&
         (cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < eps);
}

// s:segment, t:segment
bool isis_ss(Line s, Line t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
         ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

// p が l:line 上に存在するか
bool isis_lp(Line l, Point p) { return (abs(cross(l.b - p, l.a - p)) < eps); }

bool isis_sp(Line s, Point p) {
  return (abs(s.a - p) + abs(s.b - p) - abs(s.b - s.a) < eps);
}

// p から l に下ろした足との交点
Point proj(Line l, Point p) {
  ld t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + t * (l.a - l.b);
}

// l:line, t:line の交点
Point is_ll(Line l, Line m) {
  Point lv = l.b - l.a, mv = m.b - m.a;
  assert(cross(lv, mv) != 0);
  return l.a + lv * cross(mv, m.a - l.a) / cross(mv, lv);
}

// p, l:line の距離
ld dist_lp(Line l, Point p) { return abs(p - proj(l, p)); }

ld dist_ll(Line l, Line m) { return isis_ll(l, m) ? 0 : dist_lp(l, m.a); }

ld dist_ls(Line l, Line s) {
  return isis_ls(l, s) ? 0 : std::min(dist_lp(l, s.a), dist_lp(l, s.b));
}

ld dist_sp(Line s, Point p) {
  Point r = proj(s, p);
  return isis_sp(s, r) ? abs(r - p) : std::min(abs(s.a - p), abs(s.b - p));
}

ld dist_ss(Line s, Line t) {
  if (isis_ss(s, t)) return 0;
  return std::min(
      {dist_sp(s, t.a), dist_sp(s, t.b), dist_sp(t, s.a), dist_sp(t, s.b)});
}

// a, b の垂直二等分線. a -> b を90度反時計回り回転
Line bisector(Point a, Point b) {
  Point mid = (a + b) * Point(0.5, 0);
  return Line(mid, mid + (b - a) * Point(0, pi / 2));
}

// 直線 l, m のなす角を求める
ld degree_ll(Line l, Line m) {
  ld cos_shita = dot(l, m) / (abs(l.b - l.a) * abs(m.b - m.a));
  if (cos_shita < -1.0) cos_shita = -1.0;
  if (cos_shita > 1.0) cos_shita = 1.0;
  ld shita = acos(cos_shita);
  // shita = sita * 180.0 / PI;
  return shita;
}

// c1, c2 の交点
std::vector<Point> is_cc(Circle c1, Circle c2) {
  std::vector<Point> res;
  ld d = abs(c1.p - c2.p);
  ld rc = (d * d + c1.r * c1.r - c2.r * c2.r) / (2 * d);
  ld dfr = c1.r * c1.r - rc * rc;
  if (abs(dfr) < eps)
    dfr = 0.0;
  else if (dfr < 0.0)
    return res;  // no intersection
  ld rs = sqrt(dfr);
  Point diff = (c2.p - c1.p) / d;
  res.emplace_back(c1.p + diff * Point(rc, rs));
  if (dfr != 0.0) res.emplace_back(c1.p + diff * Point(rc, -rs));
  return res;
}

std::vector<Point> is_lc(Circle c, Line l) {
  std::vector<Point> res;
  ld d = dist_lp(l, c.p);
  if (d < c.r + eps) {
    ld len = (d > c.r) ? 0.0 : sqrt(c.r * c.r - d * d);  // safety;
    Point nor = (l.a - l.b) / abs(l.a - l.b);
    res.emplace_back(proj(l, c.p) + len * nor);
    res.emplace_back(proj(l, c.p) - len * nor);
  }
  return res;
}

std::vector<Point> is_sc(Circle c, Line l) {
  std::vector<Point> v = is_lc(c, l), res;
  for (Point p : v)
    if (isis_sp(l, p)) res.emplace_back(p);
  return res;
}

// p から c への接線
std::vector<Line> tangent_cp(Circle c, Point p) {
  std::vector<Line> ret;
  Point v = c.p - p;
  ld d = abs(v);
  ld l = sqrt(norm(v) - c.r * c.r);
  if (std::isnan(l)) {
    return ret;
  }
  Point v1 = v * Point(l / d, c.r / d);
  Point v2 = v * Point(l / d, -c.r / d);
  ret.emplace_back(Line(p, p + v1));
  if (l < eps) return ret;
  ret.emplace_back(Line(p, p + v2));
  return ret;
}

// c1, c2 の共通接線
std::vector<Line> tangent_cc(Circle c1, Circle c2) {
  std::vector<Line> ret;
  if (abs(c1.p - c2.p) - (c1.r + c2.r) > -eps) {
    Point center = (c1.p * c2.r + c2.p * c1.r) / (c1.r + c2.r);
    ret = tangent_cp(c1, center);
  }
  if (abs(c1.r - c2.r) > eps) {
    Point out = (-c1.p * c2.r + c2.p * c1.r) / (c1.r - c2.r);
    std::vector<Line> nret = tangent_cp(c1, out);
    ret.insert(ret.end(), nret.begin(), nret.end());
  } else {
    Point v = c2.p - c1.p;
    v /= abs(v);
    Point q1 = c1.p + v * Point(0, 1) * c1.r;
    Point q2 = c1.p + v * Point(0, -1) * c1.r;
    ret.emplace_back(Line(q1, q1 + v));
    ret.emplace_back(Line(q2, q2 + v));
  }
  return ret;
}
