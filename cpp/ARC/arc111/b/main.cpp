#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
#define SUM(c) accumulate(ALL(c), 0)
#define SUMLL(c) accumulate(ALL(c), 0LL)
#define SZ(c) ((ll)(c).size())
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << #x << " = " << (x) << '\n';
using P = pair<ll,ll>;
using VP = vector<P>;
using VVP = vector<VP>;
using VS = vector<string>;
using VI = vector<int>;
using VVI = vector<VI>;
using VVVI = vector<VVI>;
using VLL = vector<ll>;
using VVLL = vector<VLL>;
using VVVLL = vector<VVLL>;
using VB = vector<bool>;
using VVB = vector<VB>;
using VVVB = vector<VVB>;
using VD = vector<double>;
using VVD = vector<VD>;
using VVVD = vector<VVD>;
static const double EPS = 1e-10;
static const double PI  = acos(-1.0);
static const ll MOD = 1000000007;
// static const ll MOD = 998244353;
// static const int INF = (1 << 30) - 1;  // 1073741824 - 1
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------

class UnionFind {
    public:
        /**
         * @brief Construct a new Union Find object.
         * 
         * @param N Number of node.
         */
        UnionFind(int N) {
            _N = N;
            _make_set();
        }
 
        /**
         * @brief Find the root of the set containing x.
         * 
         * @param x node (1-based index).
         */
        int find(int x) {
            if (_parent[x] != x) {
                _parent[x] = find(_parent[x]);
            }
            return _parent[x];
        }
 
        /**
         * @brief Replace the set containing x and the set containing y
         *        with their union.
         * 
         * @param x node (1-based index).
         * @param y node (1-based index).
         */
        void unite(int x, int y) {
            int x_root = find(x);
            int y_root = find(y);
 
            _esize[x_root]++;
            if (x_root == y_root) return;
 
            int x_rank = _rank[x_root];
            int y_rank = _rank[y_root];
            if (x_rank > y_rank) {
                _parent[y_root] = x_root;
                _size[x_root] += _size[y_root];
                _esize[x_root] += _esize[y_root];
            } else if (x_rank < y_rank) {
                _parent[x_root] = y_root;
                _size[y_root] += _size[x_root];
                _esize[y_root] += _esize[x_root];
            } else {
                _parent[y_root] = x_root;
                _rank[x_root] += 1;
                _size[x_root] += _size[y_root];
                _esize[x_root] += _esize[y_root];
            }
        }
 
        /**
         * @brief Whether the set containing x is the same as the set containing y.
         * 
         * @param x node (1-based index).
         * @param y node (1-based index).
         */
        bool same_set(int x, int y) { return find(x) == find(y); }
 
        /**
         * @brief Number of elements in the set containing x.
         * 
         * @param x node (1-based index).
         */
        int size(int x) { return _size[find(x)]; }
 
        int esize(int x) { return _esize[find(x)]; }
 
    private:
        int _N;
        vector<int> _parent, _rank, _size, _esize;
 
        void _make_set() {
            _parent = vector<int>(_N + 1);
            iota(_parent.begin(), _parent.end(), 0);
            _rank = vector<int>(_N + 1, 0);
            _size = vector<int>(_N + 1, 1);
            _esize = vector<int>(_N + 1, 0);
        }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VLL A(N),B(N); REP(i,N) cin >> A[i] >> B[i];

    // 座標圧縮
    VLL C;
    REP(i,N) {
        C.push_back(A[i]);
        C.push_back(B[i]);
    }
    SORT(C);
    C.erase(unique(ALL(C)), C.end());
    unordered_map<ll,ll> mp;
    ll c = SZ(C);
    REP(i,c) mp[C[i]] = i;
 
    UnionFind uf(c);
    REP(i,N) {
        uf.unite(mp[A[i]], mp[B[i]]);
    }
    ll ans = 0;
    unordered_map<ll,bool> used;
    REP(i,c) {
        ll root = uf.find(i);
        if (used[root]) continue;
        used[root] = true;
        ans += min(uf.size(root), uf.esize(root));
    }
    COUT(ans);

    return 0;
}
