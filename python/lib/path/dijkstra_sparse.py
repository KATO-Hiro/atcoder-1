"""<https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm>"""
import heapq
import sys

import numba as nb
import numpy as np

input = sys.stdin.readline


# NOTE: Dijkstra algorithm with priority queue (this is slow for dense graphs)
# 1. SciPy
# 2. Python
# 3. Numba

def solve1(N, A, B, T):
    from scipy.sparse import csr_matrix
    from scipy.sparse.csgraph import dijkstra

    csgraph = csr_matrix((T, (A, B)), shape=(N, N))
    min_time = 1 << 30
    for s in range(N):
        dist_matrix = dijkstra(csgraph, indices=s)
        time = dist_matrix.max()
        if time < min_time:
            min_time = time
    return int(min_time)


def solve2(N, G):
    def dijkstra(V, G, s):
        INF = 1 << 30
        dist = [INF] * V
        dist[s] = 0

        p_queue = []
        p_queue.append((dist[s], s))
        while p_queue:
            min_dist, u = heapq.heappop(p_queue)
            if dist[u] < min_dist:
                continue
    
            for v, c in G[u]:
                alt = dist[u] + c
                if alt < dist[v]:
                    dist[v] = alt
                    heapq.heappush(p_queue, (alt, v))

        return dist

    min_time = 1 << 30
    for s in range(N):
        dist_matrix = dijkstra(N, G, s)
        time = np.max(dist_matrix)
        if time < min_time:
            min_time = time
    return min_time


@nb.njit("i8(i8,i8,i8[:,:])", cache=True)
def solve3(N, M, abt):
    def dijkstra(V, G, s):
        INF = 1 << 30
        dist = [INF] * (V + 1)
        dist[s] = 0

        p_queue = []
        p_queue.append((dist[s], s))
        while p_queue:
            min_dist, u = heapq.heappop(p_queue)
            if dist[u] < min_dist:
                continue

            for v, c in G[u][1:]:
                alt = dist[u] + c
                if alt < dist[v]:
                    dist[v] = alt
                    heapq.heappush(p_queue, (alt, v))

        return dist

    G = [[(-1, -1)] for _ in range(N + 1)]
    for i in range(M):
        a, b, t = abt[i]
        G[a].append((b, t))
        G[b].append((a, t))

    min_time = 1 << 30
    for s in range(1, N + 1):
        time = max(dijkstra(N, G, s)[1:])
        min_time = min(min_time, time)

    return min_time


def main():
    solve = 1

    # 1. SciPy
    if solve == 1:
        N, M = map(int, input().split())
        A = np.zeros(shape=2 * M, dtype=np.int64)
        B = np.zeros(shape=2 * M, dtype=np.int64)
        T = np.zeros(shape=2 * M, dtype=np.int64)
        for i in range(M):
            A[i], B[i], T[i] = map(int, input().split())

        T[M:] = T[:M]
        A[M:] = B[:M]
        B[M:] = A[:M]
        A -= 1
        B -= 1

        ans = solve(N, A, B, T)
        print(ans)

    # 2. Python
    elif solve == 2:
        N, M = map(int, input().split())
        G = [[] for _ in range(N)]
        for _ in range(M):
            a, b, t = map(int, input().split())
            a -= 1
            b -= 1
            G[a].append((b, t))
            G[b].append((a, t))

        ans = solve2(N, G)
        print(ans)

    # 3. Numba
    else:
        N, M = map(int, input().split())
        abt = np.zeros(shape=(M, 3), dtype=np.int64)
        for i in range(M):
            abt[i] = input().split()

        ans = solve3(N, M, abt)
        print(ans)


if __name__ == "__main__":
    main()

"""
<https://atcoder.jp/contests/abc012/tasks/abc012_4>

Example for input
5 5
1 2 12
2 3 14
3 4 7
4 5 9
5 1 18

26
"""
