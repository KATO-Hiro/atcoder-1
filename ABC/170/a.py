import sys

input = sys.stdin.readline


def main():
    x = list(map(int, input().split()))

    ans = x.index(0) + 1

    print(ans)


if __name__ == "__main__":
    main()
