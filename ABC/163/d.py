import sys

input = sys.stdin.readline

P = 10 ** 9 + 7


def main():
    N, K = map(int, input().split())

    ans = 0
    for k in reversed(range(1, (N+1)+1)):
        a = (N + (N-k+1))*k//2
        b = k*(k-1)//2
        ans += a - b + 1
        ans %= P

        if k == K :
            break

    print(ans)


if __name__ == "__main__":
    main()
