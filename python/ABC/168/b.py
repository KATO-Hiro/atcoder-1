import sys

input = sys.stdin.readline


def main():
    K = int(input())
    S = input().rstrip()

    N = len(S)
    if N <= K:
        ans = S
    else:
        ans = S[:K] + "..."

    print(ans)


if __name__ == "__main__":
    main()
