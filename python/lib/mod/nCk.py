from math import factorial as f


def nCk(n, k):
    return f(n) // (f(n - k) * f(k))


if __name__ == "__main__":
    print("input `n k` for nCk.")
    n, k = map(int, input().split())
    print(nCk(n, k))
