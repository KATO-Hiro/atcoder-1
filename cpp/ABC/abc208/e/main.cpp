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
using VVVVLL = vector<VVVLL>;
using VVVVVLL = vector<VVVVLL>;
using VVVVVVLL = vector<VVVVVLL>;
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
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    string N; cin >> N;
    ll K; cin >> K;
    ll L = SZ(N);
    N = " " + N;

    auto state = [](ll d, ll n0, ll n2, ll n3, ll n5, ll n7) -> tuple<ll,ll,ll,ll,ll> {
        if (d == 0) n0++;
        if (d == 2) n2++;
        if (d == 3) n3++;
        if (d == 4) n2 += 2;
        if (d == 5) n5++;
        if (d == 6) { n2++; n3++; }
        if (d == 7) n7++;
        if (d == 8) n2 += 3;
        if (d == 9) n3 += 2;
        return {n0, n2, n3, n5, n7};
    };

    vector<map<tuple<ll,ll,ll,ll,ll>,ll>> dp(L+1);
    ll m0 = 0, m2 = 0, m3 = 0, m5 = 0, m7 = 0;
    FOR(i,1,L+1) {
        ll n = N[i] - '0';

        // 先頭に非ゼロが初登場 (< N)
        if (1 < i) FOR(d,1,10) dp[i][state(d,0,0,0,0,0)] += 1;

        // N 一致状態 -> N 未満確定状態
        REP(d,n) {
            if (i == 1 && d == 0) continue;  // leading zero 回避
            dp[i][state(d,m0,m2,m3,m5,m7)] += 1;
        }

        // N 未満確定状態間の遷移
        for (auto [t, num] : dp[i-1]) {
            auto [n0, n2, n3, n5, n7] = t;
            REP(d,10) dp[i][state(d,n0,n2,n3,n5,n7)] += num;
        }

        if (n == 0) m0++;
        if (n == 2) m2++;
        if (n == 3) m3++;
        if (n == 4) m2 += 2;
        if (n == 5) m5++;
        if (n == 6) { m2++; m3++; }
        if (n == 7) m7++;
        if (n == 8) m2 += 3;
        if (n == 9) m3 += 2;
    }

    // x = N
    dp[L][state(-1,m0,m2,m3,m5,m7)] += 1;

    // 0 < x < N
    ll ans = 0;
    for (auto [t, num] : dp[L]) {
        auto [n0, n2, n3, n5, n7] = t;
        // cerr << n0 << " " << n2 << " " << n3 << " " << n5 << " " << n7 << ": " << num << endl;
        if (n0 > 0) { ans += num; continue; }
        ll tmp = 1;
        REP(_,n2) tmp *= 2;
        REP(_,n3) tmp *= 3;
        REP(_,n5) tmp *= 5;
        REP(_,n7) tmp *= 7;
        if (tmp <= K) ans += num;
    }
    COUT(ans);

    return 0;
}
