import sys

input = sys.stdin.readline


def main():
    N, D = map(int, input().split())
    X = [0] * N
    Y = [0] * N
    for i in range(N):
        X[i], Y[i] = map(int, input().split())

    D_2 = D ** 2
    ans = 0
    for x, y in zip(X, Y):
        dist = x ** 2 + y ** 2
        if dist <= D_2:
            ans += 1

    print(ans)


if __name__ == "__main__":
    main()
