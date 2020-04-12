import sys

input = sys.stdin.readline


def main():
    X, Y, Z = map(int, input().split())

    X, Y = Y, X
    X, Z = Z, X

    print("{} {} {}".format(X, Y, Z))


if __name__ == "__main__":
    main()
