import sys
input = sys.stdin.readline


def main():
    N, K = map(int, input().split())
    d = [0] * K
    A = [0] * K
    for i in range(K):
        d[i] = int(input())
        A[i] = list(map(int, input().split()))

    tmp = [0] * N
    for i in range(K):
        for a in A[i]:
            tmp[a-1] += 1

    ans = tmp.count(0)
    print(ans)


if __name__ == "__main__":
    main()
