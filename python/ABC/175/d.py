import sys
from itertools import accumulate

input = sys.stdin.readline


class UnionFind:
    """Union Find class.

    "Path compression" and "Union by rank" are used.

    References:
        <https://en.wikipedia.org/wiki/Disjoint-set_data_structure>
    """

    def __init__(self, N):
        self.N = N
        self.__make_set()

    def __make_set(self):
        self._parent = list(range(self.N + 1))
        self._rank = [0] * (self.N + 1)
        self._size = [1] * (self.N + 1)

    def find(self, x):
        if self._parent[x] != x:
            self._parent[x] = self.find(self._parent[x])
        return self._parent[x]

    def union(self, x, y):
        x_root = self.find(x)
        y_root = self.find(y)

        if x_root == y_root:
            return

        x_rank = self._rank[x_root]
        y_rank = self._rank[y_root]
        if x_rank > y_rank:
            self._parent[y_root] = x_root
            self._size[x_root] += self._size[y_root]
        elif x_rank < y_rank:
            self._parent[x_root] = y_root
            self._size[y_root] += self._size[x_root]
        else:
            self._parent[y_root] = x_root
            self._rank[x_root] += 1
            self._size[x_root] += self._size[y_root]

    def same_set(self, x, y):
        return self.find(x) == self.find(y)

    def size(self, x):
        return self._size[self.find(x)]


def main():
    N, K = map(int, input().split())
    P = list(map(int, input().split()))
    C = list(map(int, input().split()))

    uf = UnionFind(N)
    for i, p in enumerate(P, 1):
        uf.union(i, p)

    ans = -float("inf")
    visited_cc = set()
    for i in range(1, N + 1):
        cc = uf.find(i)
        if cc in visited_cc:
            continue
        visited_cc.add(cc)

        CC = []
        j = P[i - 1]
        while True:
            CC.append(C[j - 1])
            if i == j:
                break
            j = P[j - 1]
        n_CC = len(CC)
        loop_cost = sum(CC)
        CC = list(accumulate([0] + CC * 2))

        if K < n_CC:
            cost = [-float("inf")] * n_CC
            for n_move in range(1, K + 1):
                for j in range(n_CC):
                    tmp = CC[j + n_move] - CC[j]
                    cost[n_move - 1] = max(cost[n_move - 1], tmp)
            res = max(cost)
        else:
            cost = [-float("inf")] * n_CC
            for n_move in range(1, n_CC):
                for j in range(n_CC):
                    tmp = CC[j + n_move] - CC[j]
                    cost[n_move - 1] = max(cost[n_move - 1], tmp)
            q, r = divmod(K, n_CC)
            if loop_cost > 0:
                if r > 0:
                    res = max(loop_cost * q + max(cost[:r]), loop_cost * (q - 1) + max(cost))
                else:
                    res = max(loop_cost * q, loop_cost * (q - 1) + max(cost))
            else:
                res = max(cost)

        ans = max(ans, res)

    print(ans)


if __name__ == "__main__":
    main()
