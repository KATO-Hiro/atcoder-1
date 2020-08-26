import sys
input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))

    ans = 0
    b = {}
    for i in range(N):
        l = A[i] + (i+1)
        r = (i+1) - A[i]
        if r in b:
            ans += b[r]
        if l in b:
            b[l] += 1
        else:
            b[l] = 1

    print(ans)


if __name__ == "__main__":
    main()
