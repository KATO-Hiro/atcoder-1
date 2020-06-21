import sys

input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))

    all_xor = A[0]
    for a in A[1:]:
        all_xor = all_xor ^ a

    ans = [a ^ all_xor for a in A]
    print(" ".join(map(str, ans)))


if __name__ == "__main__":
    main()
