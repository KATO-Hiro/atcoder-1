import sys

input = sys.stdin.readline


def main():
    A, V = map(int, input().split())
    B, W = map(int, input().split())
    T = int(input())

    if A < B:
        if A + V * T >= B + W * T:
            ans = "YES"
        else:
            ans = "NO"
    else:
        if A - V * T <= B - W * T:
            ans = "YES"
        else:
            ans = "NO"

    print(ans)


if __name__ == "__main__":
    main()
