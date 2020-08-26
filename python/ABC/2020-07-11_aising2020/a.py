import sys

input = sys.stdin.readline


def main():
    L, R, d = map(int, input().split())

    ans = 0
    for i in range(L, R + 1):
        ans += 1 if i % d == 0 else 0

    print(ans)


if __name__ == "__main__":
    main()
