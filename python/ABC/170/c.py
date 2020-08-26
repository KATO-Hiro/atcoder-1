import sys

input = sys.stdin.readline


def main():
    X, N = map(int, input().split())
    p = list(map(int, input().split()))

    i = 0
    while True:
        if X - i not in p:
            ans = X - i
            break
        if X + i not in p:
            ans = X + i
            break
        i += 1

    print(ans)


if __name__ == "__main__":
    main()
