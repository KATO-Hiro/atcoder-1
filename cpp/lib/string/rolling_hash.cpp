#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------


// References
//   <https://qiita.com/keymoon/items/11fac5627672a6d6a9f6>
//   <https://atcoder.jp/contests/abc141/submissions/11668413>
//   <https://atcoder.jp/contests/abc150/submissions/9414606>
//   <https://drken1215.hatenablog.com/entry/2019/09/16/014600>

struct Rolling_Hash {
    static constexpr ll MOD = (1LL << 61) - 1;
    static constexpr ll base1 = 10007;
    static constexpr ll base2 = 10091;

    int N;
    vector<ll> hash1, hash2, pow1, pow2;

    Rolling_Hash() {}

    void build(const string& S) {
        int n = S.size();
        vector<ll> s(n);
        for (int i = 0; i < n; i++) { s[i] = (ll)S[i]; }
        build(s);
    }

    void build(const vector<ll>& s) {
        N = (int)s.size();
        hash1.resize(N+1, 0); pow1.resize(N+1, 1);
        hash2.resize(N+1, 0); pow2.resize(N+1, 1);
        for(int i = 0; i < N; i++) {
            hash1[i+1] = mul(hash1[i], base1) + s[i];
            hash2[i+1] = mul(hash2[i], base2) + s[i];
            pow1[i+1] = mul(pow1[i], base1);
            pow2[i+1] = mul(pow2[i], base2);
            if (hash1[i+1] >= MOD) hash1[i+1] -= MOD;
            if (hash2[i+1] >= MOD) hash2[i+1] -= MOD;
        }
    }

    ll mul(__int128_t a, __int128_t b) const {
        __int128_t t = a * b;
        t = (t >> 61) + (t & MOD);
        if (t >= MOD) t -= MOD;
        return t;
    }

    // hash [l,r)
    pair<ll,ll> hash(int l, int r) {
        assert(0 <= l); assert(l <= r); assert(r <= N);
        ll res1 = hash1[r] - mul(hash1[l], pow1[r-l]);
        ll res2 = hash2[r] - mul(hash2[l], pow2[r-l]);
        if (res1 < 0) res1 += MOD;
        if (res2 < 0) res2 += MOD;
        return make_pair(res1, res2);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);

    string S; cin >> S;
    string T; cin >> T;

    ll N = S.size();
    ll M = T.size();

    Rolling_Hash rhS, rhT;
    rhS.build(S); rhT.build(T);

    REP(i,N-(M-1)) {
        if (rhS.hash(i,i+M) == rhT.hash(0,M)) {
            cout << i << '\n';
        }
    }

    return 0;
}
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja
