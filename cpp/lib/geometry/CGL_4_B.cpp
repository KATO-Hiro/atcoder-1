#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (int i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define MIN(c) *min_element(ALL(c))
#define MAX(c) *max_element(ALL(c))
#define SUM(c) accumulate(ALL(c), 0)
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((int)(c).size())
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << #x << " = " << (x) << '\n';
using P = pair<int,int>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VD = vector<double>;
using VVD = vector<VD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
static const int INF = (1 << 30) - 1;  // 1073741824 - 1
// static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
// #include <atcoder/all>
// using namespace atcoder;

// 微小値 EPS の誤差を許容して a, b が等価であるか判定する
inline bool eq(double a, double b) { return fabs(a - b) < EPS; }

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

    // pair<x, y> の要領で大小比較（x昇順 --> y昇順）
    bool operator < (const Point& p) const noexcept {
        return x != p.x ? x < p.x : y < p.y;
    }

    bool operator == (const Point& p) const noexcept {
        return eq(x, p.x) && eq(y, p.y);
    }
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

static const int COUNTER_CLOCKWISE = 1;  // 反時計回り (左回り)
static const int CLOCKWISE = -1;         // 時計回り   (右回り)
static const int ONLINE_BACK = 2;        // 線分後方
static const int ONLINE_FRONT = -2;      // 線分前方
static const int ON_SEGMENT = 0;         // 線分上

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
// 直線と線分の交差判定
// 端点だけ重なる場合や平行に重なる場合も交差しているとみなされる
bool is_intersected(const Line& l, const Segment& s) {
    return (ccw(l.p1, l.p2, s.p1) * ccw(l.p1, l.p2, s.p2) <= 0);
}
// 線分上に点が存在するか判定
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
// 直線の交点を求める
// 直線 l1,l2 が交点を持ち平行に重なっていないことを想定
Point cross_point(const Line& l1, const Line& l2) {
    Point a = l1.p1, b = l1.p2;
    Point c = l2.p1, d = l2.p2;
    return a + (b - a) * cross(c - a, d - c) / cross(b - a, d - c);
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

// 円周上に点が存在するか判定
bool on_circle(const Circle& c, const Point& p) {
    return eq(c.r, distance(c.c, p));
}
// 円と直線が接するか判定
bool on_circle(const Circle& c, const Line& l) {
    return eq(c.r, distance(c.c, l));
}
// 直線上に点が存在するか判定
bool on_line(const Line& l, const Point& p) {
    return eq(distance(p, l), 0.0);
}

// 円と直線の交差判定
// 接している場合も交差しているとみなされる
bool is_intersected(const Circle& c, const Line& l) {
    if (on_circle(c.c, l)) return true;
    return distance(c.c, l) < c.r;
}

// 円の交差判定
// 2つの円の共通接線の数を計算する
//   4本: 離れている
//   3本: 外接
//   2本: 2点交差
//   1本: 内接
//   0本: 内包
int circle_intersection(const Circle& c1, const Circle& c2) {
    int n;  // 共通接線の数
    double d = distance(c1.c, c2.c);
    double r1 = c1.r, r2 = c2.r;
    if (r1 > r2) swap(r1, r2);  // r1 <= r2
    if (r1 + r2 < d) {
        n = 4; 
    } else if (eq(r1 + r2, d)) {
        n = 3;
    } else if (d + r1 > r2) {
        n = 2;
    } else if (eq(d + r1, r2)) {
        n = 1;
    } else {  // d + r1 < r2
        n = 0;
    }
    return n;
}

// 円の交差判定
// 外接・2点交差・内接の場合に交差していると判定する
bool is_intersected(const Circle& c1, const Circle& c2) {
    int n = circle_intersection(c1, c2);
    return (n == 3 || n == 2 || n == 1) ? true : false;
}

// 円と直線の交点を求める
// 円と直線が交差していることを想定
// ただし，接している場合は接点が2つ返される
pair<Point, Point> cross_point(const Circle& c, const Line& l) {
    assert(is_intersected(c, l));
    Point pr = projection(l, c.c);
    Point e = (l.p2 - l.p1) / abs(l.p2 - l.p1);
    double base = sqrt(c.r * c.r - norm(pr - c.c));
    return make_pair(pr + e * base, pr - e * base);
}

// 偏角を求める (argument)
double arg(const Point& p) { return atan2(p.y, p.x); }

// 極座標系から直交座標系に変換する
Point polar2carte(const double& r, const double& theta) {
    return Point(r * cos(theta), r * sin(theta));
}

// 円と円の交点を求める
// 円と円が交差していることを想定
// ただし，接している場合は接点が2つ返される
pair<Point, Point> cross_point(const Circle& c1, const Circle& c2) {
    assert(is_intersected(c1, c2));
    double d = distance(c1.c, c2.c);
    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));  // 余弦定理
    double t = arg(c2.c - c1.c);
    return make_pair(c1.c + polar2carte(c1.r, t + a), c1.c + polar2carte(c1.r, t - a));
}

// 点 p を通る円 c の接線を求める
// 点 p が円 c の外側に存在することを想定
pair<Point, Point> tangent_point(const Point& p, const Circle& c) {
    // 三平方の定理より点 p と接点の距離 d が得られるため，
    // 点 p を中心とする半径 d の円と円 c の交点を求めればよい
    double d = sqrt(norm(c.c - p) - c.r * c.r);
    return cross_point(c, Circle(p, d));
}

// 2つの円の共通接線を求める
// Lines common_tangent(const Circle& c1, const Circle& c2) {
//     ;  // TODO
// }

// 2点を直径とする円を求める
Circle circle_with_2pt_as_diameter(const Point& p1, const Point& p2) {
    return Circle((p1 + p2) / 2, distance(p1, p2) / 2);
}

// 三角形の面積を求める
double area_of_triangle(const Point& A, const Point& B, const Point& C) {
    double a = abs(B - C);
    double b = abs(C - A);
    double c = abs(A - B);
    double s = (a + b + c) / 2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
}

// 三角形の内接円を求める
// 3点が同じ直線上に存在しない想定
// <https://ja.wikipedia.org/wiki/%E4%B8%89%E8%A7%92%E5%BD%A2%E3%81%AE%E5%86%85%E6%8E%A5%E5%86%86%E3%81%A8%E5%82%8D%E6%8E%A5%E5%86%86>
Circle incircle_of_triangle(const Point& A, const Point& B, const Point& C) {
    double a = abs(B - C);
    double b = abs(C - A);
    double c = abs(A - B);
    double d = a + b + c;
    double s = d / 2;
    double S = sqrt(s*(s-a)*(s-b)*(s-c));
    double r = 2*S / d;
    Point I = A*(a/d) + B*(b/d) + C*(c/d);
    return Circle(I, r);
}

// 三角形の外接円を求める
// 3点が同じ直線上に存在しない想定
// <https://ja.wikipedia.org/wiki/%E5%A4%96%E6%8E%A5%E5%86%86>
Circle circumscribed_circle_of_triangle(const Point& A, const Point& B, const Point& C) {
    double a2 = norm(B - C);
    double b2 = norm(C - A);
    double c2 = norm(A - B);
    double x = a2 * (b2 + c2 - a2);
    double y = b2 * (c2 + a2 - b2);
    double z = c2 * (a2 + b2 - c2);
    double w = x + y + z;  // 情報落ち対策のため x/w などとしている
    Point O = A*(x/w) + B*(y/w) + C*(z/w);  // 外心
    double R = distance(O, A);  // 外接円の半径
    return Circle(O, R);
}

// 多角形の面積を求める
//   - 頂点数≧3
//   - 頂点列が反時計回りであることを想定
//   - 多角形が自己交差していないことを想定
// <https://ja.wikipedia.org/wiki/%E5%A4%9A%E8%A7%92%E5%BD%A2>
double area_of_polygon(const Polygon& P) {
    const int N = (int)P.size();
    assert(N >= 3);
    double area = 0.0;
    for (int i = 0; i < N; i++) {
        area += cross(P[i], P[(i+1) % N]);  // N番目の次は1番目
    }
    return area / 2;
}

// 凸性判定 (多角形が凸多角形であるか判定)
//   - 頂点数≧3
//   - 頂点列が反時計回りであることを想定
//   - 多角形が自己交差していないことを想定
bool is_convex(const Polygon& P) {
    const int N = (int)P.size();
    assert(N >= 3);
    for (int i = 0; i < N; i++) {
        if (ccw(P[(i-1+N)%N], P[i], P[(i+1+N)%N]) == CLOCKWISE) return false;
    }
    return true;
}

// 多角形における点の内包判定
// 0: 外側, 1: 線分上, 2: 内側
int point_containment(const Polygon& g, const Point& p) {
    const int N = (int)g.size();
    bool x = false;
    for (int i = 0; i < N; i++) {
        Point a = g[i] - p;
        Point b = g[(i+1)%N] - p;  // N番目の次は1番目
        if (abs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1;  // 線分上
        if (a.y > b.y) swap(a, b);
        if (a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;  // 半直線との交差回数の偶奇
    }
    return (x ? 2 : 0);
}

// 凸包を求める (Andrew's Monotone Chain)
//   - 頂点数≧3
//   - on_edge: 凸包の辺上の点を含めるか
//   - 凸包の頂点の順序は最も左の頂点から時計回り (右回り)
Polygon convex_hull(Polygon P, bool on_edge = true) {
    const int N = (int)P.size();
    assert(N >= 3);
    sort(P.begin(), P.end());  // x昇順 --> y昇順
    Polygon ch(2*N,{-1,-1});
    int k = 0;
    if (on_edge) {
        // 上包 (upper hull)
        for (int i = 0; i < N; ch[k++] = P[i++]) {
            while (k >= 2 && ccw(ch[k-2], ch[k-1], P[i]) == COUNTER_CLOCKWISE) k--;
        }
        // 下包 (lower hull)
        const int t = k + 1;
        for (int i = N-2; 0 <= i; ch[k++] = P[i--]) {
            while (k >= t && ccw(ch[k-2], ch[k-1], P[i]) == COUNTER_CLOCKWISE) k--;
        }
    } else {
        // 上包 (upper hull)
        for (int i = 0; i < N; ch[k++] = P[i++]) {
            while (k >= 2 && ccw(ch[k-2], ch[k-1], P[i]) != CLOCKWISE) k--;
        }
        // 下包 (lower hull)
        const int t = k + 1;
        for (int i = N-2; 0 <= i; ch[k++] = P[i--]) {
            while (k >= t && ccw(ch[k-2], ch[k-1], P[i]) != CLOCKWISE) k--;
        }
    }
    ch.resize(k-1);
    return ch;
}

// 凸多角形を直線で切断したとき左側にできる凸多角形を求める
//   - 頂点数≧3
//   - 頂点列が反時計回りであることを想定
//   - 直線上に位置する頂点も結果に含まれる
//   - 求めた凸多角形の頂点数が 0〜2 になる可能性あり (面積計算等で注意)
Polygon convex_cut(const Polygon& P, const Line& l) {
    const int N = (int)P.size();
    assert(N >= 3);
    Polygon cc;
    Point p1 = l.p1;
    Point p2 = l.p2;
    for (int i = 0; i < N; i++) {
        Point a = P[i];
        Point b = P[(i+1)%N];  // N番目の次は1番目
        Segment s(a, b);
        // 1. 点 a が直線の左側に位置すれば cc に追加 (直線上にある場合も含む)
        if (ccw(p1, p2, a) != CLOCKWISE) {
            cc.push_back(a);
        }
        // 2. 線分 ab が直線と交差すれば交点を cc に追加 (端点の場合は含めない)
        if (!on_line(l, a) && !on_line(l, b) && is_intersected(l, s)) {
            cc.push_back(cross_point(l, Line(a, b)));
        }
    }
    return cc;
}

// 凸多角形の直径を求める（最遠点対間距離）
double convex_diameter(const Polygon& P) {
    Polygon Q = convex_hull(P, true);
    reverse(Q.begin(), Q.end());  // 下記では反時計回りを想定しているため
    const int N = (int)Q.size();
    if (N == 2) { return distance(Q[0], Q[1]); }
    int i = 0, j = 0;  // 最遠点対
    for (int k = 1; k < N; k++) {  // x軸方向の最遠点対で初期化
        if (Q[k] < Q[i]) i = k;  // 最も左側
        if (Q[j] < Q[k]) j = k;  // 最も右側
    }
    double res = 0;
    int si = i, sj = j;  // 終了判定用
    while (i != sj || j != si) {  // 反時計回りに180度まで回転しながら解析
        res = max(res, distance(Q[i], Q[j]));
        // 符号付き面積を利用して次の最遠点対が Q_{i+1}, Q_{j+1} のどちらか決定
        if (cross(Q[(i+1)%N] - Q[i], Q[(j+1)%N] - Q[j]) < 0) {
            i = (i + 1) % N;
        } else {
            j = (j + 1) % N;
        }
    }
    return res;
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N; cin >> N;
    Polygon P(N); REP(i,N) cin >> P[i].x >> P[i].y;

    double ans = convex_diameter(P);
    cout << ans << endl;

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B&lang=ja
