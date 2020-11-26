// References:
//   『プログラミングコンテスト攻略のためのアルゴリズムとデータ構造』
//   <https://github.com/atcoder/live_library/blob/master/geom/vector.cpp>
//   <https://ei1333.github.io/luzhiled/snippets/geometry/template.html>

// 点 (ベクトル)
struct Point {
    double x, y;
    Point(double x = 0, double y = 0): x(x), y(y) {}

    Point& operator+=(const Point& v) noexcept { x += v.x; y += v.y; return *this; }
    Point& operator-=(const Point& v) noexcept { x -= v.x; y -= v.y; return *this; }
    Point& operator*=(double k) noexcept { x *= k; y *= k; return *this; }
    Point& operator/=(double k) noexcept { x /= k; y /= k; return *this; }

    Point operator+(const Point& v) const noexcept { return Point(*this) += v; }
    Point operator-(const Point& v) const noexcept { return Point(*this) -= v; }
    Point operator*(double k) const noexcept { return Point(*this) *= k; }
    Point operator/(double k) const noexcept { return Point(*this) /= k; }

    double norm() const noexcept { return x*x + y*y; }  // ベクトルの大きさ
    double abs() const noexcept { return sqrt(norm()); }  // 原点からの距離，ベクトルの長さ
};

// 直線
struct Line {
    Point p1, p2;
    Line(Point p1 = Point(), Point p2 = Point()): p1(p1), p2(p2) {}
};

// 線分
struct Segment {
    Point p1, p2;
    Segment(Point p1 = Point(), Point p2 = Point()): p1(p1), p2(p2) {}
};

// 円
struct Circle {
    Point c;  // 中心
    double r;  // 半径
    Circle(Point c = Point(), double r = 0.0): c(c), r(r) {}
};

using Points = vector<Point>;
using Polygon = vector<Point>;  // 多角形
using Segments = vector<Segment>;
using Lines = vector<Line>;
using Circles = vector<Circle>;

double norm(const Point& a) { return a.x*a.x + a.y*a.y; }  // ベクトルの大きさ
double abs(const Point& a) { return sqrt(norm(a)); }  // 原点からの距離，ベクトルの長さ
double dot(const Point& a, const Point& b) { return a.x*b.x + a.y*b.y; }  // 内積
double cross(const Point& a, const Point& b) { return a.x*b.y - a.y*b.x; }  // 外積

// 微小値 EPS の誤差を許容して a, b が等価であるか判定する
inline bool eq(double a, double b) { return fabs(a - b) < EPS; }

// 射影: 直線 l に点 p から垂線を引いたときの交点を求める
Point projection(const Line& l, const Point& p) {
    Point base = l.p2 - l.p1;
    double t = dot(p - l.p1, base) / norm(base);
    return l.p1 + base * t;
}
// 射影: 線分 s に点 p から垂線を引いたときの交点を求める
// ※ 交点が線分上に存在するかは別途判定する必要あり --> on_segment()
Point projection(const Segment& s, const Point& p) {
    Point base = s.p2 - s.p1;
    double t = dot(p - s.p1, base) / norm(base);
    return s.p1 + base * t;
}

// 反射: 直線 l を対称軸として点 p と線対称にある点を求める
Point reflection(const Line& l, const Point& p) {
    return p + (projection(l, p) - p) * 2.0;
}
// 反射: 線分 s を対称軸として点 p と線対称にある点を求める
// ※ 線分が交差するかは別途判定する必要あり --> is_intersected()
Point reflection(const Segment& s, const Point& p) {
    return p + (projection(s, p) - p) * 2.0;
}

// 直行判定 (直線)
bool is_orthogonal(const Line& a, const Line& b) {
    return eq(dot(a.p1 - a.p2, b.p1 - b.p2), 0.0);
}
// 直行判定 (線分)
// ※ 線分の交差判定を先に行う必要あり --> is_intersected()
bool is_orthogonal(const Segment& a, const Segment& b) {
    return eq(dot(a.p1 - a.p2, b.p1 - b.p2), 0.0);
}

// 平行判定 (直線)
bool is_parallel(const Line& a, const Line& b) {
    return eq(cross(a.p1 - a.p2, b.p1 - b.p2), 0.0);
}
// 平行判定 (線分)
bool is_parallel(const Segment& a, const Segment& b) {
    return eq(cross(a.p1 - a.p2, b.p1 - b.p2), 0.0);
}

static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

// 3点 p0,p1,p2 の位置関係を線分 p1 - p0 を基準にして求める
int ccw(const Point& p0, const Point& p1, const Point& p2) {
    Point a = p1 - p0;
    Point b = p2 - p0;
    if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;  // p0 -> p1, 反時計回りの方向に p2
    if (cross(a, b) < -EPS) return CLOCKWISE;         // p0 -> p1,   時計回りの方向に p2
    if (dot(a, b) < -EPS) return ONLINE_BACK;         // p2 -> p0 -> p1 の順で直線上に p2
    if (a.norm() < b.norm()) return ONLINE_FRONT;     // p0 -> p1 -> p2 の順で直線上に p2
    return ON_SEGMENT;                                // p0 -> p2 -> p1 の順で線分上に p2
}

// 線分の交差判定
// 端点だけ重なる場合や平行に重なる場合も交差しているとみなされる
bool is_intersected(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
    return (ccw(p1,p2,p3) * ccw(p1,p2,p4) <= 0) && (ccw(p3,p4,p1) * ccw(p3,p4,p2) <= 0);
}
// 線分の交差判定
// 端点だけ重なる場合や平行に重なる場合も交差しているとみなされる
bool is_intersected(const Segment& s1, const Segment& s2) {
    return is_intersected(s1.p1, s1.p2, s2.p1, s2.p2);
}
// 線分上に点が存在するか判定する
bool on_segment(const Segment& s, const Point& p) {
    return ccw(s.p1, s.p2, p) == ON_SEGMENT;
}

// 線分の交点を求める
// 線分 s1,s2 が交点を持ち平行に重なっていないことを想定
Point cross_point(const Segment& s1, const Segment& s2) {
    Point base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1));
    double d2 = abs(cross(base, s1.p2 - s2.p1));
    assert(d1 > EPS || d2 > EPS);
    return s1.p1 + (s1.p2 - s1.p1) * (d1 / (d1 + d2));
}

// 2点間の距離
double distance(const Point& a, const Point& b) { return abs(a - b); }

// 点と直線の距離
double distance(const Point& p, const Line& l) { return abs(p - projection(l, p)); }

// 点と線分の距離
double distance(const Point& p, const Segment& s) {
    Point m = projection(s, p);
    if (on_segment(s, m)) return abs(p - m);
    return min(abs(s.p1 - p), abs(s.p2 - p));
}

// 線分と線分の距離
double distance(const Segment& a, const Segment& b) {
    if (is_intersected(a, b)) return 0.0;
    return min({distance(a.p1, b), distance(a.p2, b), distance(b.p1, a), distance(b.p2, a)});
}
