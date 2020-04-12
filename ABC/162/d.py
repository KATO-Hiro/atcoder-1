import sys

input = sys.stdin.readline


def main():
    N = int(input())
    S = input().rstrip()

    R = []
    G = []
    B = []
    for i in range(N):
        if S[i] == "R":
            R.append(i)
        elif S[i] == "G":
            G.append(i)
        else:
            B.append(i)

    n_R = len(R)
    n_G = len(G)
    n_B = len(B)
    ans = n_R * n_G * n_B
    if ans == 0:
        print(ans)
        exit()

    for r in R:
        for g in G:
            rg = sorted([r, g])
            dist = rg[1] - rg[0]
            if 0 <= rg[0] - dist:
                if S[rg[0] - dist] == "B":
                    ans -= 1
            if rg[1] + dist <= N - 1:
                if S[rg[1] + dist] == "B":
                    ans -= 1
            if dist % 2 == 0:
                if S[rg[0] + (dist // 2)] == "B":
                    ans -= 1
    print(ans)


if __name__ == "__main__":
    main()
