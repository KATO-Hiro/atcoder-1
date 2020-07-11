import sys

input = sys.stdin.readline


def main():
    N = int(input())

    f = [0] * (N + 1)
    for x in range(1, 10 ** 2 + 1):
        for y in range(1, 10 ** 2 + 1):
            for z in range(1, 10 ** 2 + 1):
                n = x ** 2 + y ** 2 + z ** 2 + x * y + y * z + z * x
                if n <= N:
                    f[n] += 1

    print("\n".join(map(str, f[1:])))


if __name__ == "__main__":
    main()
