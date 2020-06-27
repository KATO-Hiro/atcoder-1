import sys

input = sys.stdin.readline


def main():
    S = input().rstrip()
    T = input().rstrip()

    ans = 0
    for s, t in zip(S, T):
        if s != t:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
