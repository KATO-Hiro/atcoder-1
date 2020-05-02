import sys
input = sys.stdin.readline


def main():
    X = int(input())

    Y = 100
    i = 1
    while True:
        Y = int(Y * 1.01)
        if Y >= X:
            ans = i
            break
        i += 1
    print(ans)


if __name__ == "__main__":
    main()
