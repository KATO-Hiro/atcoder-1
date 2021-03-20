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
#define SZ(c) ((ll)(c).size())
#define BIT(b,i) (((b)>>(i)) & 1)
#define PCNT(b) __builtin_popcountll(b)
#define CIN(c) cin >> (c)
#define COUT(c) cout << (c) << '\n'
#define debug(x) cerr << "l." << __LINE__ << " : " << #x << " = " << (x) << '\n'
ll llceil(ll a, ll b) { return (a + b - 1) / b; }
string toupper(const string& S) { string T(S); REP(i,SZ(T)) T[i] = toupper(T[i]); return T; }
string tolower(const string& S) { string T(S); REP(i,SZ(T)) T[i] = tolower(T[i]); return T; }
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
#include <atcoder/maxflow>
using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll H, W, A, B; cin >> H >> W >> A >> B;

    ll ans = 0;
    ll N = H*W;
    REP(S,1<<N) if (PCNT(S) == B) {
        VVLL C(H,VLL(W,0));
        REP(i,N) if (BIT(S,i)) {
            ll h = i / W;
            ll w = i % W;
            C[h][w] = 1;
        }
        VVB D(H,VB(W,false));
        auto rec = [&](auto self, ll i, ll j) -> ll {
            if (j == W) return self(self, i+1, 0);
            if (i == H) return 1;
            if (D[i][j] || C[i][j]) return self(self, i, j+1);

            ll res = 0;
            D[i][j] = true;

            if (j+1 < W && !D[i][j+1] && !C[i][j+1]) {
                D[i][j+1] = true;
                res += self(self, i, j+1);
                D[i][j+1] = false;
            }

            if (i+1 < H && !D[i+1][j] && !C[i+1][j]) {
                D[i+1][j] = true;
                res += self(self, i, j+1);
                D[i+1][j] = false;
            }

            D[i][j] = false;
            return res;
        };
        ans += rec(rec, 0, 0);
    }
    COUT(ans);

    return 0;
}
