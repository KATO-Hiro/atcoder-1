import sys

input = sys.stdin.readline


def is_prime_number(n):
    if n == 1:
        return False

    if n == 2:
        return True

    if n % 2 == 0:
        return False

    f = 3
    root_n = int(n ** 0.5) + 1
    while f <= root_n:
        if n % f == 0:
            return False
        f += 2

    return True


def main():
    N = int(input())
    ans = is_prime_number(N)
    print(ans)


if __name__ == "__main__":
    main()
