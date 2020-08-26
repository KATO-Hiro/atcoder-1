"""<https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm>"""
import sys

import numba as nb
import numpy as np

input = sys.stdin.readline


# Dijkstra algorithm without priority queue (this is slow for sparse graphs)
@nb.njit("i8[:](i8,i8[:,:],i8,i8)", cache=True)
def dijkstra(V, G, s, INF):
    # Shortest path from vertex s
    dist = np.full(shape=V, fill_value=INF, dtype=np.int64)
    dist[s] = 0

    unvisited = [True] * V

    while len(unvisited) != 0:
        min_dist = INF
        u = -1
        for v in range(V):
            if unvisited[v] and dist[v] < min_dist:
                min_dist = dist[v]
                u = v

        # when planning a complete traversal; occurs when there is no connection
        # between the initial node and remaining unvisited nodes
        if min_dist == INF:
            break

        unvisited[u] = False

        for v in range(V):
            if unvisited[v] and G[u][v] != INF:
                alt = dist[u] + G[u][v]
                if alt < dist[v]:
                    dist[v] = alt

    return dist


def main():
    N = int(input())
    INF = 1 << 30
    G = np.full(shape=(N, N), fill_value=INF, dtype=np.int64)
    for _ in range(N):
        u, k, *vc = map(int, input().split())
        for i in range(k):
            v = vc[2 * i]
            c = vc[2 * i + 1]
            G[u][v] = c

    for s in range(N):
        print(s, dijkstra(N, G, s, INF))


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
