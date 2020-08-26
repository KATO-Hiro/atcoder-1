import sys

input = sys.stdin.readline


def main():
    A, B, C = map(int, input().split())
    K = int(input())

    M = 0
    while True:
        if A < B:
            break
        else:
            B *= 2
            M += 1
    while True:
        if B < C:
            break
        else:
            C *= 2
            M += 1

    if M <= K:
        ans = "Yes"
    else:
        ans = "No"

    print(ans)


if __name__ == "__main__":
    main()
