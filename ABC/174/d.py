import sys

input = sys.stdin.readline


def main():
    N = int(input())
    C = input().rstrip()

    l = 0
    r = N - 1
    ans = 0
    while True:
        if C[l] == "W" and C[r] == "R":
            ans += 1
            l += 1
            r -= 1
        elif C[l] == "R" and C[r] == "R":
            l += 1
        elif C[l] == "W" and C[r] == "W":
            r -= 1
        else:
            l += 1
            r -= 1

        if not l < r:
            break

    print(ans)


if __name__ == "__main__":
    main()
