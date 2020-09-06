#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


/**
 * @brief Union Find class.
 * 
 * @details "Path compression" and "Union by rank" are used.
 * @see <https://en.wikipedia.org/wiki/Disjoint-set_data_structure>
 */
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

        int find(int x) {
            if (_parent[x] != x) {
                _parent[x] = find(_parent[x]);
            }
            return _parent[x];
        }

        void unite(int x, int y) {
            int x_root = find(x);
            int y_root = find(y);

            if (x_root == y_root) return;

            int x_rank = _rank[x_root];
            int y_rank = _rank[y_root];
            if (x_rank > y_rank) {
                _parent[y_root] = x_root;
                _size[x_root] += _size[y_root];
            } else if (x_rank < y_rank) {
                _parent[x_root] = y_root;
                _size[y_root] += _size[x_root];
            } else {
                _parent[y_root] = x_root;
                _rank[x_root] += 1;
                _size[x_root] += _size[y_root];
            }
        }

        bool same_set(int x, int y) { return find(x) == find(y); }

        int size(int x) { return _size[find(x)]; }


    private:
        int _N;
        vector<int> _parent, _rank, _size;

        void _make_set() {
            _parent = vector<int>(_N + 1);
            iota(_parent.begin(), _parent.end(), 0);
            _rank = vector<int>(_N + 1, 0);
            _size = vector<int>(_N + 1, 1);
        }

};


// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A
int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<ll>> stw(E, vector<ll>(3));
    int s, t, w;
    rep(i, E) {
        cin >> s >> t >> w;
        stw[i] = {s, t, w};
    }
    sort(stw.begin(), stw.end(), [](auto a, auto b) {return a[2] < b[2];});

    auto uf = UnionFind(V);

    ll ans = 0;
    for (auto x : stw) {
        s = x[0] + 1;  // For AOJ input type (0-based)
        t = x[1] + 1;  // For AOJ input type (0-based)
        w = x[2];
        if (uf.same_set(s, t)) continue;
        uf.unite(s, t);
        ans += w;
    }
    cout << ans << endl;

    return 0;
}