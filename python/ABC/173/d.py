import sys
import heapq

input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))

    A.sort(reverse=True)
    A = [-a for a in A]

    q = [A[0]]
    heapq.heapify(q)
    ans = 0
    for a in A[1:]:
        max_v = heapq.heappop(q)
        ans += max_v
        heapq.heappush(q, a)
        heapq.heappush(q, a)

    ans = -ans
    print(ans)


if __name__ == "__main__":
    main()
