"""<https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm>"""
import sys

import numpy as np
from scipy.sparse import csr_matrix
from scipy.sparse.csgraph import dijkstra

input = sys.stdin.readline


# Dijkstra algorithm with priority queue (this is slow for dense graphs)
def main():
    N = int(input())

    INF = 1 << 30
    G = [[INF] * N for _ in range(N)]
    for _ in range(N):
        u, k, *vc = map(int, input().split())
        for i in range(k):
            v = vc[2 * i]
            c = vc[2 * i + 1]
            G[u][v] = c

    csgraph = csr_matrix(G)
    for s in range(N):
        dist_matrix = dijkstra(csgraph, indices=s)
        print(s, dist_matrix.astype(np.int64))


if __name__ == "__main__":
    main()

"""
<https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/12/ALDS1_12_B>

Example for input
5
0 3 2 3 3 1 1 2
1 2 0 2 3 4
2 3 0 3 3 1 4 1
3 4 2 1 0 1 1 4 4 3
4 2 2 1 3 3

0 [0 2 2 1 3]
1 [2 0 4 3 5]
2 [2 4 0 1 1]
3 [1 3 1 0 2]
4 [3 5 1 2 0]
"""
