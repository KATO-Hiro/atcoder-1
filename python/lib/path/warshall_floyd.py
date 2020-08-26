import sys

import numba as nb
import numpy as np

input = sys.stdin.readline


@nb.njit("void(i8,i8[:,:],i8)", cache=True)
def warshall_floyd(n, d, INF):
    for k in range(n):
        for i in range(n):
            d_ik = d[i][k]
            if d_ik == INF:
                continue
            for j in range(n):
                if d[i][j] > d_ik + d[k][j]:
                    d[i][j] = d_ik + d[k][j]


def main():
    V, E = map(int, input().split())

    # NOTE: (max cost of the problem) < INF << (max value of the dtype)
    #   e.g.) 1 <= V <= 100, 1 <= cost <= 1000
    #         Then, max cost is 99 * 1000
    #         - np.iinfo(np.int64).max: 9223372036854775807
    #         - np.iinfo(np.int32).max: 2147483647
    INF = 100 * 1000

    # shortest path
    dist = np.full(shape=(V, V), fill_value=INF, dtype=np.int64)

    # 0 cost for 'loop'
    for i in range(V):
        dist[i][i] = 0

    for _ in range(E):
        s, t, d = map(int, input().split())
        s -= 1
        t -= 1
        dist[s][t] = d
        dist[t][s] = d
        # ^^^ delete for directed graph

    warshall_floyd(V, dist, INF)

    print(*dist, sep="\n")


if __name__ == "__main__":
    main()

"""
<http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C&lang=ja>

Example for input
4 6
1 2 1
1 3 5
2 3 2
2 4 4
3 4 1
4 3 7

[0, 1, 3, 5]
[1, 0, 2, 4]
[3, 2, 0, 6]
[5, 4, 6, 0]
"""
