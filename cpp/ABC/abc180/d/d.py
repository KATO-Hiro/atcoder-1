import sys

input = sys.stdin.readline


def main():
    X, Y, A, B = map(int, input().split())

    ans = 0
    while True:
        XX = A * X
        if XX >= Y:
            ans += (Y - X - 1) // B
            break
        dX = XX - X
        if B <= dX:
            ans += (Y - X - 1) // B
            break
        X *= A
        ans += 1

    print(ans)


if __name__ == "__main__":
    main()
