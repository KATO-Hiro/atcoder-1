import sys

input = sys.stdin.readline


def main():
    X, Y = map(int, input().split())

    if 2 * X <= Y <= 4 * X and Y % 2 == 0:
        ans = "Yes"
    else:
        ans = "No"

    print(ans)


if __name__ == "__main__":
    main()
