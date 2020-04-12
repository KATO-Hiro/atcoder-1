from collections import deque


def bfs(H, W, maze, dist, sh, sw):
    queue = deque([[sh, sw]])
    dist[sh][sw] = 0
    while queue:
        h, w = queue.popleft()
        for i, j in [(1, 0), (-1, 0), (0, -1), (0, 1)]:
            next_h, next_w = h + i, w + j
            if not ((0 <= next_h <= H - 1) and (0 <= next_w <= W - 1)):
                continue
            if (maze[next_h][next_w] == ".") and (dist[next_h][next_w] == -1):
                dist[next_h][next_w] = dist[h][w] + 1
                queue.append([next_h, next_w])
    return dist


if __name__ == "__main__":
    H = 4
    W = 4
    S = [None] * H
    S[0] = ".##."
    S[1] = "..#."
    S[2] = ".#.."
    S[3] = "...."
    sh, sw = 0, 0
    gh, gw = 0, 3
    for i in range(H):
        print(S[i])

    dist = [[-1] * W for _ in range(H)]
    dist = bfs(H, W, S, dist, sh, sw)
    for i in range(H):
        print(dist[i])

    print("Start=({},{}), Goal=({},{}): {}".format(
        sh, sw, gh, gw, dist[gh][gw]))
