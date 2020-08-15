import sys

input = sys.stdin.readline


def main():
    X, K, D = map(int, input().split())

    X = abs(X)
    q, r = divmod(X, D)
    if K <= q:
        ans = (q - K) * D + r
    else:
        if (K - q) % 2 == 0:
            ans = r
        else:
            ans = D - r

    print(ans)


if __name__ == "__main__":
    main()
