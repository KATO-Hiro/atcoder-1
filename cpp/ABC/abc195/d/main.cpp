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
// #include <atcoder/all>
// using namespace atcoder;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, M, Q; cin >> N >> M >> Q;
    VP WV(N); REP(i,N) cin >> WV[i].first >> WV[i].second;
    VLL X(M); REP(i,M) cin >> X[i];

    sort(ALL(WV), [](P p1, P p2) { return (p1.first == p2.first ? (p1.second > p2.second) : (p1.first < p2.first)); });

    while (Q--) {
        ll L, R; cin >> L >> R;
        L--; R--;
        priority_queue<ll,VLL,greater<ll>> pq;
        REP(i,M) if (i < L || R < i) {
            pq.push(X[i]);
        }
        priority_queue<ll> A;
        ll a = 0;

        ll ans = 0;
        while (!pq.empty()) {
            ll x = pq.top(); pq.pop();
            // 補充
            while (a < N) {
                auto [w, v] = WV[a];
                if (w <= x) {
                    A.push(v);
                    a++;
                } else {
                    break;
                }
            }
            // 格納
            if (!A.empty()) {
                ans += A.top(); A.pop();
            }
        }
        COUT(ans);
    }


    return 0;
}
