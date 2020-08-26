import sys

input = sys.stdin.readline


def main():
    N, K = map(int, input().split())

    _, r = divmod(N, K)
    ans = min(abs(r - K), r, r + K)
    print(ans)


if __name__ == "__main__":
    main()
