

def dfs(G, v, p, d):
    """G: graph, v: vertex, p: parent"""
    d[v] = d[p] + 1
    # Loop for each child
    for c in G[v]:
        if c == p:
            continue
        dfs(G, c, v, d)


def main():
    N = int(input())
    G = [[] for _ in range(N)]
    for _ in range(N - 1):
        u, v = map(int, input().split())
        u -= 1
        v -= 1
        G[u].append(v)
        G[v].append(u)

    depth = [-1] * N
    depth[0] = 0
    dfs(G, 0, -1, depth)
    print(*depth, sep="\n")


if __name__ == "__main__":
    main()

"""
Example for input
7
1 2
1 3
2 4
2 5
3 6
3 7
"""
