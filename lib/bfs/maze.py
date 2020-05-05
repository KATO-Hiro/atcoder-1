import sys
from collections import deque

import numpy as np

input = sys.stdin.readline


def bfs(H, W, grid, dist, sh, sw):
    queue = deque([[sh, sw]])
    dist[sh][sw] = 0
    while queue:
        h, w = queue.popleft()
        for i, j in [(1, 0), (-1, 0), (0, -1), (0, 1)]:
            next_h, next_w = h + i, w + j
            if not ((0 <= next_h <= H - 1) and (0 <= next_w <= W - 1)):
                continue
            if grid[next_h][next_w] and (dist[next_h][next_w] == -1):
                dist[next_h][next_w] = dist[h][w] + 1
                queue.append([next_h, next_w])


if __name__ == "__main__":
    H, W = map(int, input().split())
    S = np.full((H, W), False, dtype=bool)
    for i in range(H):
        S[i] = [True if s == "." else False for s in input().rstrip()]

    sh, sw = 0, 0
    gh, gw = 0, 3

    dist = [[-1] * W for _ in range(H)]
    bfs(H, W, S, dist, sh, sw)
    print("----debug----")
    print(*dist, sep="\n")

    print("Start=({},{}), Goal=({},{}): {}".format(
        sh, sw, gh, gw, dist[gh][gw]))

"""
Example for input
4 4
.##.
..#.
.#..
....
"""
