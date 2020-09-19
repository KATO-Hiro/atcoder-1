#include <bits/stdc++.h>
using namespace std;
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


ll mod_pow(ll x, ll n, ll mod) {
    ll res = 1;
    if (n > 0) {
        res = mod_pow(x, n / 2, mod);
        if (n % 2 == 0) res = (res * res) % mod;
        else res = (((res * res) % mod) * x) % mod;
    }
    return res;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    ll N, X, M; cin >> N >> X >> M;

    VLL A(M);
    REP(i, M) {
        A[i] = mod_pow((ll)i, 2, M);
    }

    VLL B;
    B.push_back(X);
    VB found(M, false);
    ll l = 0;
    REP(_, M) {
        ll C = A[B.back()];
        if (found[C]) {
            l = find(ALL(B), C) - B.begin();
            break;
        }
        found[C] = true;
        B.push_back(C);
    }

    ll loop_len = (SZ(B) - l);
    ll ans = 0;
    if (N <= l) {
        REP(i,N) ans += B[i];
    } else {
        REP(i,l) ans += B[i];
        ll q = (N - l) / loop_len;
        ll r = (N - l) % loop_len;
        ll sum_B = 0;
        FOR(i, l, SZ(B)) {
            sum_B += B[i];
        }
        ans += sum_B * q;
        FOR(i,l,l+r) ans += B[i];
    }
    cout << ans << '\n';

    return 0;
}
