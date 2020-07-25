import sys

input = sys.stdin.readline


def main():
    N = int(input())
    A = list(map(int, input().split()))

    ans = 1000
    ll = rr = A[0]
    status = "down"
    for a in A[1:]:
        if status == "down":
            if ll < a:
                status = "up"
                rr = a
            else:
                ll = a
        else:
            if rr <= a:
                rr = a
            else:
                status = "down"
                q, r = divmod(ans, ll)
                ans = rr * q + r
                ll = a

    if status == "up":
        q, r = divmod(ans, ll)
        ans = rr * q + r

    print(ans)


if __name__ == "__main__":
    main()
