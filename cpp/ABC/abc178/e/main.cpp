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


struct P {
    ll x, y;
    P() {};
    P(ll x, ll y) : x(x), y(y) {
    }
    P operator + (P p) {
        return P(x + p.x, y + p.y);
    }
    P operator - (P p) {
        return P(x - p.x, y - p.y);
    }
    P operator * (ll d) {
        return P(x * d, y * d);
    }
    ll dot(P p) {
        return (x * p.x) + (y * p.y);
    }
    ll det(P p) {
        return (x * p.y) + (-y * p.x);
    }
};


ll dist(P p, P q) {
    return llabs(p.x - q.x) + llabs(p.y - q.y);
}


bool cmp_x(const P& p, const P& q) {
    if (p.x != q.x) return p.x < q.x;
    return p.y < q.y;
}


vector<P> convex_hull(P* ps, int n) {
    sort(ps, ps + n, cmp_x);
    int k = 0;
    vector<P> qs(n * 2);

    for (int i = 0; i < n; i++) {
        while (k > 1 && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    for (int i = n - 2, t = k; i >= 0; i--) {
        while (k > t && (qs[k - 1] - qs[k - 2]).det(ps[i] - qs[k - 1]) <= 0) k--;
        qs[k++] = ps[i];
    }
    qs.resize(k - 1);
    return qs;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(10);

    int N; cin >> N;
    P ps[N];
    REP(i, N) {
        ll x, y; cin >> x >> y;
        ps[i] = P(x, y);
    }

    vector<P> qs = convex_hull(ps, N);
    ll ans = 0;
    for (int i = 0; i < SZ(qs); i++) {
        for (int j = 0; j < i; j++) {
            ans = max(ans, dist(qs[i], qs[j]));
        }
    }
    cout << ans << '\n';

    return 0;
}
