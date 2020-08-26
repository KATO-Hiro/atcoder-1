import sys

input = sys.stdin.readline


def main():
    N = int(input())

    r = N % 1000
    if r == 0:
        ans = 0
    else:
        ans = 1000 - r

    print(ans)


if __name__ == "__main__":
    main()
