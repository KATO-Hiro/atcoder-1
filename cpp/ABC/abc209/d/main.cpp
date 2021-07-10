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
// #include <atcoder/all>
// using namespace atcoder;


struct LCA {
    int N, root, K;  // 頂点数，根，二進表記の桁数（ダブリング用）
    vector<vector<int>> G;
    vector<vector<int>> parent;  // parent[k][u]: 頂点 u から 2^k 回親を辿って到達する頂点 (根を越えたら -1)
    vector<int> depth;  // depth[u] := 頂点 u の根からの深さ

    LCA(int n, int r = 0) : N(n), root(r) {
        assert(0 <= root && root < N);
        K = 1; while ((1<<K) <= N) { K++; }
        G.resize(N);
        parent.resize(K, vector<int>(N));
        depth.resize(N);
    }

    // 双方向に辺を張る
    void add_edge(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void build() {
        // 初期化
        auto dfs = [&](auto self, int u, int p, int d) -> void {
            parent[0][u] = p;
            depth[u] = d;
            for (int v : G[u]) if (v != p) {
                self(self, v, u, d+1);
            }
        };
        dfs(dfs, root, -1, 0);

        // ダブリング
        for (int k = 1; k < K; k++) {
            for (int u = 0; u < N; u++) {
                if (parent[k-1][u] < 0) {
                    parent[k][u] = -1;
                } else {
                    parent[k][u] = parent[k-1][parent[k-1][u]];
                }
            }
        }
    }

    // 頂点 u から深さ d だけ親を辿る (level-ancestor)
    // 辿った先が木上にあることを想定している
    //   - d <= depth[u]
    int la(int u, int d) {
        assert(0 <= u && u < N);
        for (int k = K-1; 0 <= k; k--) if (BIT(d, k)) {
            u = parent[k][u];
        }
        return u;
    }

    // 頂点 u, v の LCA
    int query(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        if (depth[u] < depth[v]) swap(u, v);
        // depth[u] >= depth[v]
        u = la(u, depth[u] - depth[v]);  // (u, v) の深さを揃える
        if (u == v) return u;
        for (int k = K-1; 0 <= k; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    // (u, v) パス間の辺数
    int distance(int u, int v) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        return depth[u] + depth[v] - 2*depth[query(u, v)];
    }

    // 頂点 w が (u, v) パス上に存在するか
    bool on_path(int u, int v, int w) {
        assert(0 <= u && u < N);
        assert(0 <= v && v < N);
        assert(0 <= w && w < N);
        return distance(u, w) + distance(w, v) == distance(u, v);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    LCA lca(N, 0);
    REP(_,N-1) {
        ll u, v; cin >> u >> v;
        u--; v--;
        lca.add_edge(u, v);
    }
    lca.build();

    while (Q--) {
        ll c, d; cin >> c >> d;
        c--; d--;
        ll res = lca.distance(c, d);
        string ans = (res % 2 == 1 ? "Road" : "Town");
        COUT(ans);
    }

    return 0;
}
