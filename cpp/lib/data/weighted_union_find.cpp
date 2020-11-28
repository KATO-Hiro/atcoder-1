#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


/**
 * @brief Weighted Union Find class.
 * 
 * @details "Path compression" and "Union by rank" are used.
 * @see <https://en.wikipedia.org/wiki/Disjoint-set_data_structure>
 */
class WeightedUnionFind {
    public:
        /**
         * @brief Construct a new Union Find object.
         * 
         * @param N Number of node.
         */
        WeightedUnionFind(int N) {
            _N = N;
            _make_set();
        }

        /**
         * @brief Find the root of the set containing x.
         * 
         * @param x node (0-based index).
         */
        int find(int x) {
            if (_parent[x] == x) return x;
            int x_root = find(_parent[x]);
            _dW[x] += _dW[_parent[x]];  // cumsum from root to x
            return _parent[x] = x_root;
        }

        /**
         * @brief Merge the two sets so that `W(x) + w = W(y)`.
         * 
         * @param x node (0-based index).
         * @param y node (0-based index).
         * @param w weight.
         */
        bool unite(int x, int y, ll w) {
            int x_root = find(x);
            int y_root = find(y);
            if (x_root == y_root) return false;

            w = w + dW(x) - dW(y);
            int x_rank = _rank[x_root];
            int y_rank = _rank[y_root];
            if (x_rank == y_rank) _rank[x_root]++;
            if (x_rank >= y_rank) {
                _parent[y_root] = x_root;
                _size[x_root] += _size[y_root];
                _dW[y_root] = w;
            } else {
                _parent[x_root] = y_root;
                _size[y_root] += _size[x_root];
                _dW[x_root] = -w;
            }
            return true;
        }

        /**
         * @brief Calculate `W(y) - W(x)` when x and y are in the same set.
         * 
         * @param x node (0-based index).
         * @param y node (0-based index).
         */
        ll diff(int x, int y) {
            assert(same_set(x, y));
            return dW(y) - dW(x);
        }

        /**
         * @brief Whether the set containing x is the same as the set containing y.
         * 
         * @param x node (0-based index).
         * @param y node (0-based index).
         */
        bool same_set(int x, int y) { return find(x) == find(y); }

        /**
         * @brief Number of elements in the set containing x.
         * 
         * @param x node (0-based index).
         */
        int size(int x) { return _size[find(x)]; }

    private:
        int _N;
        vector<int> _parent, _rank, _size;
        vector<ll> _dW;  // _dW[x] := W(x) - W(x's parent)

        void _make_set() {
            _parent = vector<int>(_N); iota(_parent.begin(), _parent.end(), 0);
            _rank = vector<int>(_N, 0);
            _size = vector<int>(_N, 1);
            _dW = vector<ll>(_N, 0);
        }

        ll dW(int x) {
            find(x);  // path compression
            return _dW[x];
        }
};


int main() {
    int N, Q; cin >> N >> Q;

    WeightedUnionFind wuf(N);
    int q, x, y;
    ll z;
    rep(_, Q) {
        cin >> q >> x >> y;
        if (q == 0) {
            cin >> z;
            wuf.unite(x, y, z);
        } else {
            if (wuf.same_set(x, y)) {
                cout << wuf.diff(x, y) << '\n';
            } else {
                cout << "?" << '\n';
            }
        }
    }

    return 0;
}
// Verify: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=ja
