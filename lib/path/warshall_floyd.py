import sys
input = sys.stdin.readline

INF = float("inf")


def warshall_floyd(n, d):
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

    # shortest path
    dist = [[INF] * V for _ in range(V)]

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

    warshall_floyd(V, dist)

    print(*dist, sep="\n")


if __name__ == "__main__":
    main()

"""
Example for input
4 6
1 2 1
1 3 5
2 3 2
2 4 4
3 4 1
4 3 7
"""
