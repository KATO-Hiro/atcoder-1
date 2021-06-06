#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
// --------------------------------------------------------

// References:
//   <https://naoyat.hatenablog.jp/entry/zeta-moebius>
//   <https://qiita.com/convexineq/items/afc84dfb9ee4ec4a67d5#_reference-6897e76b2cb2ee712901>
//   <https://primenumber.hatenadiary.jp/entry/2016/12/01/000000>
//   <https://misteer.hatenablog.com/entry/zeta-moebius>
//   <https://habara-k.hatenadiary.jp/entry/2020/04/14/010237>
//   <https://blog.hamayanhamayan.com/entry/2017/05/20/125607>

// 計算量 O(N 2^N)

// 高速ゼータ関数 (1) : S⊆T タイプ
//   g(S) = sum_{S⊆T} f(T)
template <class T>
vector<T> fast_zeta_transform_1(const vector<T>& f) {
    int N = f.size();
    vector<T> g(f);
    for (int i = 0; i < N; i++) {
        for (int S = 0; S < (1<<N); S++) {
            if (((S>>i) & 1) == 0) {
                g[S] += g[S ^ (1<<i)];
            }
        }
    }
    return g;
}

// 高速ゼータ関数 (2) : T⊆S タイプ
// g(S) = sum_{T⊆S} f(T)
template <class T>
vector<T> fast_zeta_transform_2(const vector<T>& f) {
    int N = f.size();
    vector<T> g(f);
    for (int i = 0; i < N; i++) {
        for (int S = 0; S < (1<<N); S++) {
            if (((S>>i) & 1) == 1) {
                g[S] += g[S ^ (1<<i)];
            }
        }
    }
    return g;
}

// 高速メビウス関数 (1) : S⊆T タイプ
//   f(S) = sum_{S⊆T} (-1)^{|T-S|} g(T)
template <class T>
vector<T> fast_moebius_transform_1(const vector<T>& g) {
    int N = g.size();
    vector<T> f(g);
    for (int i = 0; i < N; i++) {
        for (int S = 0; S < (1<<N); S++) {
            if (((S>>i) & 1) == 0) {
                f[S] -= f[S ^ (1<<i)];
            }
        }
    }
    return f;
}

// 高速メビウス関数 (2) : T⊆S タイプ
//   f(S) = sum_{T⊆S} (-1)^{|S-T|} g(T)
template <class T>
vector<T> fast_moebius_transform_2(const vector<T>& g) {
    int N = g.size();
    vector<T> f(g);
    for (int i = 0; i < N; i++) {
        for (int S = 0; S < (1<<N); S++) {
            if (((S>>i) & 1) == 1) {
                f[S] -= f[S ^ (1<<i)];
            }
        }
    }
    return f;
}


// TODO: verify
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);


    return 0;
}
