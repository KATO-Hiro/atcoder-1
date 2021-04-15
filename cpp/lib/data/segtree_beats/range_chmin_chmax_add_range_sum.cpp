#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
using VLL = vector<ll>;
static const ll INF = (1LL << 62) - 1;  // 4611686018427387904 - 1
// --------------------------------------------------------


#include "segtree_beats.cpp"

// 区間 chmin|chmax|add ・区間総和
//   Base: <https://rsm9.hatenablog.com/entry/2021/02/01/220408#Library-Checker-Range-Chmin-Chmax-Add-Range-Sum>
struct S {
    ll lo1, lo2, nlo;  // 最小値・(厳密な)二番目の最小値・最小値の個数
    ll hi1, hi2, nhi;  // 最大値・(厳密な)二番目の最大値・最大値の個数
    ll sum, num;       // 区間和・区間要素数
    bool fail;
    S() : lo1(INF), lo2(INF), nlo(0), hi1(-INF), hi2(-INF), nhi(0), sum(0), num(0), fail(false) {}
    S(ll x, ll n = 1) : lo1(x), lo2(INF), nlo(n), hi1(x), hi2(-INF), nhi(n), sum(x*n), num(n), fail(false) {}
};
struct F {
    ll lb, ub, b;
    F(ll chmax_ = -INF, ll chmin_ = INF, ll add = 0) : lb(chmax_), ub(chmin_), b(add) {}
    static F chmin(ll x) noexcept { return F(-INF, x, 0); }
    static F chmax(ll x) noexcept { return F(x, INF, 0); }
    static F add(ll x) noexcept { return F(-INF, INF, x); };
};
S e() { return S(); }
S op(S l, S r) {
    S res;
    res.lo1 = min(l.lo1, r.lo1);
    res.hi1 = max(l.hi1, r.hi1);
    res.lo2 = (l.lo1 == r.lo1 ? min(l.lo2, r.lo2) : (l.lo2 <= r.lo1 ? l.lo2 : (r.lo2 <= l.lo1 ? r.lo2 : max(l.lo1, r.lo1))));
    res.hi2 = (l.hi1 == r.hi1 ? max(l.hi2, r.hi2) : (l.hi2 >= r.hi1 ? l.hi2 : (r.hi2 >= l.hi1 ? r.hi2 : min(l.hi1, r.hi1))));
    res.nlo = l.nlo * (l.lo1 <= r.lo1) + r.nlo * (l.lo1 >= r.lo1);
    res.nhi = l.nhi * (l.hi1 >= r.hi1) + r.nhi * (l.hi1 <= r.hi1);
    res.sum = l.sum + r.sum;
    res.num = l.num + r.num;
    return res;
}
S mapping(F f, S x) {
    if (x.num == 0) return e();
    if (x.lo1 == x.hi1 || f.lb == f.ub || f.lb >= x.hi1 || f.ub < x.lo1) {
        return S(min(max(x.lo1, f.lb), f.ub) + f.b, x.num);
    }
    if (x.lo2 == x.hi1) {
        x.lo1 = x.hi2 = max(x.lo1, f.lb) + f.b;
        x.hi1 = x.lo2 = min(x.hi1, f.ub) + f.b;
        x.sum = x.lo1 * x.nlo + x.hi1 * x.nhi;
        return x;
    }
    if (f.lb < x.lo2 && f.ub > x.hi2) {
        ll nxt_lo1 = max(x.lo1, f.lb);
        ll nxt_hi1 = min(x.hi1, f.ub);
        x.sum += (nxt_lo1 - x.lo1) * x.nlo - (x.hi1 - nxt_hi1) * x.nhi + f.b * x.num;
        x.lo1 = nxt_lo1 + f.b;
        x.hi1 = nxt_hi1 + f.b;
        x.lo2 += f.b;
        x.hi2 += f.b;
        return x;
    }
    x.fail = true;
    return x;
}
F composition(F fnew, F fold) {
    F res;
    res.lb = max(min(fold.lb + fold.b, fnew.ub), fnew.lb) - fold.b;
    res.ub = min(max(fold.ub + fold.b, fnew.lb), fnew.ub) - fold.b;
    res.b = fold.b + fnew.b;
    return res;
}
F id() { return F(); }


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N, Q; cin >> N >> Q;
    vector<S> A(N);
    REP(i,N) {
        ll a; cin >> a;
        A[i] = a;
    }
    segtree_beats<S, op, e, F, mapping, composition, id> seg(A);
    while (Q--) {
        ll q, l, r; cin >> q >> l >> r;
        if (q <= 2) {
            ll b; cin >> b;
            if (q == 0) seg.apply(l, r, F::chmin(b));
            if (q == 1) seg.apply(l, r, F::chmax(b));
            if (q == 2) seg.apply(l, r, F::add(b));
        } else {
            ll ans = seg.prod(l, r).sum;
            cout << ans << '\n';
        }
    }

    return 0;
}
// Verify: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
