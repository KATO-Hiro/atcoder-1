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
// static const int INF = 1 << 30;  // 1073741824
// static const ll INF = 1LL << 62;  // 4611686018427387904
// --------------------------------------------------------
#include <atcoder/lazysegtree>
using namespace atcoder;

static const int INF = numeric_limits<int>::max();
using S = int;
struct F {
    int x;
};
S op(S a, S b) { return min(a, b); }
S e() { return INF; }
S mapping(F f, S x) { return (f.x == -1) ? x : f.x; }
F composition(F f, F g) { return (f.x == -1) ? g : f; }
F id() { return F{-1}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N, Q; cin >> N >> Q;
    VI A(N, INF);
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    REP(_, Q) {
        int q; cin >> q;
        if (q == 0) {
            int s, t, x; cin >> s >> t >> x;
            seg.apply(s, t + 1, F{x});
        } else {
            int s, t; cin >> s >> t;
            cout << seg.prod(s, t + 1) << '\n';
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja
