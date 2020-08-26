import sys

input = sys.stdin.readline
INF = 10 ** 18


def main():
    N = int(input())
    A = list(map(int, input().split()))

    if 0 in A:
        ans = 0
    else:
        ans = 1
        for a in A:
            ans *= a
            if ans > INF:
                ans = -1
                break

    print(ans)


if __name__ == "__main__":
    main()
