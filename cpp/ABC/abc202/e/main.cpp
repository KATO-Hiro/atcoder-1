#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// --------------------------------------------------------
template<class T> bool chmax(T& a, const T b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T b) { if (b < a) { a = b; return 1; } return 0; }
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define RFOR(i,l,r) for (ll i = (r)-1; (l) <= i; --i)
#define REP(i,n) FOR(i,0,n)
#define RREP(i,n) RFOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
#define RALL(c) (c).rbegin(), (c).rend()
#define SORT(c) sort(ALL(c))
#define RSORT(c) sort(RALL(c))
#define MIN(c) *min_element(ALL(c))
#define MAX(c) *max_element(ALL(c))
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define COUNT(c,v) count(ALL(c),(v))
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) (((b)>>(i)) & 1)
#define PCNT(b) __builtin_popcountll(b)
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << "l." << __LINE__ << " : " << #x << " = " << (x) << '\n'
ll llceil(ll a, ll b) { return (a + b - 1) / b; }
ll bitlen(ll b) { if (b <= 0) { return 0; } return (64LL - __builtin_clzll(b)); }
string toupper(const string& S) { string T(S); REP(i,SZ(T)) T[i] = toupper(T[i]); return T; }
string tolower(const string& S) { string T(S); REP(i,SZ(T)) T[i] = tolower(T[i]); return T; }
template<class T> void cout_line(const vector<T>& ans, ll l, ll r) { for (ll i = l; i < r; i++) { if (i != l) { cout << " "; } cout << ans[i]; } cout << '\n'; }
template<class T> void debug_line(const vector<T>& ans, ll l, ll r, ll L = 0) { cerr << "l." << L << " :"; for (ll i = l; i < r; i++) { cerr << " " << ans[i]; } cerr << '\n'; }
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VVS = vector<VS>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VVVLL = vector<VVLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VVVB = vector<VVB>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
using VLD = vector<ld>;
using VVLD = vector<VLD>;
using VVVLD = vector<VVLD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------
#include <atcoder/segtree>
using namespace atcoder;

// 1点加算・区間総和
using S = ll;
S op(S a, S b) { return a + b; }
S e() { return 0; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VVLL G(N);
    FOR(u,1,N) {
        ll p; cin >> p;
        p--;
        G[u].push_back(p);
        G[p].push_back(u);
    }

    ll Q; cin >> Q;
    VLL U(Q),D(Q); REP(i,Q) cin >> U[i] >> D[i];

    VVP E(N);
    REP(i,Q) {
        ll u = U[i]; u--;
        ll d = D[i];
        E[u].push_back(P(d,i));
    }

    segtree<S, op, e> seg(N);
    VLL ans(Q,0);
    auto rec = [&](auto self, ll u, ll p, ll d) -> void {
        for (auto [dd, i] : E[u]) {
            if (d > dd) continue;
            ans[i] -= seg.prod(dd, dd+1);
        }
        seg.set(d, seg.get(d) + 1);
        for (ll v : G[u]) if (v != p) {
            self(self, v, u, d+1);
        }

        for (auto [dd, i] : E[u]) {
            if (d > dd) continue;
            ans[i] += seg.prod(dd, dd+1);
        }
    };
    rec(rec, 0, -1, 0);

    for (ll a : ans) COUT(a);

    return 0;
}
