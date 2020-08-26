import sys

input = sys.stdin.readline


def main():
    N, K = map(int, input().split())
    A = list(map(int, input().split()))

    visited = [False] * N
    visited[0] = True
    path = [1]
    loop_s_idx = -1
    loop_e_idx = -1
    a = 1
    while True:
        a = A[a - 1]
        if visited[a - 1]:
            loop_s_idx = path.index(a)
            loop_e_idx = len(path) - 1
            break
        else:
            visited[a - 1] = True
            path.append(a)

    if K < len(path):
        ans = path[K]
    else:
        loop_length = loop_e_idx - loop_s_idx + 1
        q, r, = divmod(K - loop_s_idx, loop_length)
        ans = path[loop_s_idx + r]

    print(ans)


if __name__ == "__main__":
    main()
