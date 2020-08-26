import sys
from collections import deque

input = sys.stdin.readline


def bfs(G, v, check):
    queue = deque([v])
    while queue:
        v = queue.popleft()
        for u in G[v]:
            if check[u] != -1:
                continue
            check[u] = v + 1
            queue.append(u)


def main():
    N, M = map(int, input().split())
    G = [[] for _ in range(N)]
    for _ in range(M):
        A, B = map(int, input().split())
        A -= 1
        B -= 1
        G[A].append(B)
        G[B].append(A)

    check = [-1] * N
    check[0] = 0
    bfs(G, 0, check)

    print("Yes")
    print(*check[1:], sep="\n")


if __name__ == "__main__":
    main()
