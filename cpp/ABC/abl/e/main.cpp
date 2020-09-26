#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using ll = long long;
// --------------------------------------------------------
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
static const int INF = 1 << 30;
// static const ll INF = 1LL << 62;
// --------------------------------------------------------


using mint = modint998244353;

int N;
static const int MAX_N = 200000;
vector<vector<mint>> T(10, vector<mint>(MAX_N + 1, 0));

// lazy segtree
struct S {
    mint a;
    int l, r;
};
struct F {
    int D;
};
S op(S x, S y) { return S{x.a + y.a, min(x.l, y.l), max(x.r, y.r)}; }
S e() { return S{0, INF, -INF}; }
S mapping(F f, S x) {
    if (f.D == 0) return x;
    return S{T[f.D][N+1-x.l] - T[f.D][N+1-x.r - 1], x.l, x.r};
}
F composition(F f, F g) {
    if (f.D == 0) {
        return g;
    } else if (g.D == 0) {
        return f;
    }
    return f;
}
F id() { return F{0}; }
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);
 
    int Q; cin >> N >> Q;
    vector<S> A(N); REP(i,N) A[i] = S{mint(10).pow(N-i-1),i+1,i+1};
    lazy_segtree<S, op, e, F, mapping, composition, id> seg(A);

    // cumsum preprocessing
    FOR(d,1,10) FOR(i,1,MAX_N+1) T[d][i] = T[d][i-1] + mint(d) * mint(10).pow(i-1);

    int L, R, D;
    REP(_, Q) {
        cin >> L >> R >> D;
        seg.apply(L-1, R, F{D});
        cout << seg.all_prod().a.val() << '\n';
    }
 
    return 0;
}