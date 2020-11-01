#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (int i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define MIN(c) *min_element(ALL(c))
#define MAX(c) *max_element(ALL(c))
#define SUM(c) accumulate(ALL(c), 0)
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((int)(c).size())
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
static const int INF = 1 << 30;  // 1073741824
// static const ll INF = 1LL << 62;  // 4611686018427387904
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

struct S {
    ll v; int num;
};
struct F {
    ll x;
};
S op(S a, S b) { return S{a.v + b.v, a.num + b.num}; }
S e() { return S{0, 0}; }
S mapping(F f, S a) { return (f.x == INF) ? a : S{f.x * a.num, a.num}; }
F composition(F f, F g) { return (f.x == INF) ? g : f; }
F id() { return F{INF}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N, Q; cin >> N >> Q;
    vector<S> A(N, S{0, 1});
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    REP(_, Q) {
        int q; cin >> q;
        if (q == 0) {
            int s, t; cin >> s >> t;
            ll x; cin >> x;
            seg.apply(s, t + 1, F{x});
        } else {
            int s, t; cin >> s >> t;
            cout << seg.prod(s, t + 1).v << '\n';
        }
    }
    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I&lang=ja