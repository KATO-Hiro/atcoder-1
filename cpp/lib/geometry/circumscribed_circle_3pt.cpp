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

#include "geom.cpp"


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    int N; cin >> N;
    Points p(N);
    REP(i,N) {
        cin >> p[i].x >> p[i].y;
    }

    double ans = INF;
    REP(i,N-1) FOR(j,i+1,N) {
        Circle c = circle_with_2pts_as_diameter(p[i], p[j]);
        bool ok = true;
        REP(k,N) {
            if (k == i || k == j) continue;
            if (c.r < distance(c.c, p[k])) ok = false;
        }
        if (ok) chmin(ans, c.r);
    }
    REP(i1,N-2) FOR(i2,i1+1,N-1) FOR(i3,i2+1,N) {
        Circle c = circumscribed_circle(p[i1], p[i2], p[i3]);
        bool ok = true;
        REP(k,N) {
            if (k == i1 || k == i2 || k == i3) continue;
            if (c.r < distance(c.c, p[k])) ok = false;
        }
        if (ok) chmin(ans, c.r);
    }
    COUT(ans);

    return 0;
}
// Verify: https://atcoder.jp/contests/abc151/tasks/abc151_f
