import sys

input = sys.stdin.readline


def main():
    S = input().rstrip()
    T = input().rstrip()

    if S == T[:-1]:
        ans = "Yes"
    else:
        ans = "No"

    print(ans)


if __name__ == "__main__":
    main()
