import sys

input = sys.stdin.readline


def main():
    X = int(input())

    if X >= 30:
        ans = "Yes"
    else:
        ans = "No"

    print(ans)


if __name__ == "__main__":
    main()
