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
            _rank = vector<int>(_N, 0);
            _size = vector<int>(_N, 1);
        }

};


int main() {
    int N, Q;
    cin >> N >> Q;

    auto uf = UnionFind(N);
    int P, A, B;
    vector<string> ans;
    rep(_, Q) {
        cin >> P >> A >> B;
        if (P == 0) {
            uf.unite(A, B);
        } else {
            bool is_same = uf.same_set(A, B);
            ans.push_back(is_same ? "Yes" : "No");
        }
    }
    for (string s: ans) cout << s << endl;

    return 0;
}

/*
https://atcoder.jp/contests/atc001/tasks/unionfind_a

Input 1
-------
8 9
0 1 2
0 3 2
1 1 3
1 1 4
0 2 4
1 4 1
0 4 2
0 0 0
1 0 0

Output 1
--------
Yes
No
Yes
Yes

*/
