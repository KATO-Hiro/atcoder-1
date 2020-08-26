import sys

input = sys.stdin.readline

P = 2019

def main():
    S = input().rstrip()

    n = len(S)
    counts = [0] * P
    counts[0] += 1
    T = 0
    d = 1
    for s in reversed(S):
        T = (T + (d * int(s)) % P) % P
        d = (d * 10) % P
        counts[T] += 1

    ans = 0
    for c in counts:
        ans += c*(c-1)//2  # cC2
    print(ans)


if __name__ == "__main__":
    main()
