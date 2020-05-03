import sys
input = sys.stdin.readline


def main():
    N, M = map(int, input().split())
    H = list(map(int, input().split()))

    G = [[] for _ in range(N)]
    for i in range(M):
        A, B = map(int, input().split())
        A -= 1
        B -= 1
        G[A].append(B)
        G[B].append(A)

    ans = 0
    for i in range(N):
        good = True
        for p in G[i]:
            if not H[i] > H[p]:
                good = False
        ans += 1 if good else 0
    print(ans)


if __name__ == "__main__":
    main()
