import sys

input = sys.stdin.readline


def main():
    K = int(input())

    L = []
    n1 = [[i + 1] for i in range(9)]
    L.append(n1)
    cnt = 0
    if 1 <= K <= 9:
        print(K)
        exit()
    else:
        cnt += 9

    # 10 ~ 99
    n2 = [[] for _ in range(9)]
    L.append(n2)
    for i in range(9):
        base = 11 * (i + 1)
        if i != 8:
            L[1][i].extend([base - 1, base, base + 1])
        else:
            L[1][i].extend([base - 1, base])
        if K <= cnt + len(L[1][i]):
            print(L[1][i][K - cnt - 1])
            exit()
        else:
            cnt += len(L[1][i])

    k = 2
    while True:
        n = [[] for _ in range(9)]
        L.append(n)
        for i in range(9):
            base = (10 ** k) * (i + 1)
            if i == 0:
                ll = []
                ll += [base, base + 1]
                if k >= 3:
                    for m in range(2, k):
                        ll += [base + j for j in L[m-1][0]]
                ll += [base + j for j in L[k-1][i]]
                ll += [base + j for j in L[k-1][i + 1]]
                L[k][i].extend(ll)
            elif i < 8:
                ll = []
                ll += [base + j for j in L[k-1][i - 1]]
                ll += [base + j for j in L[k-1][i]]
                ll += [base + j for j in L[k-1][i + 1]]
                L[k][i].extend(ll)
            else:
                ll = []
                ll += [base + j for j in L[k-1][i - 1]]
                ll += [base + j for j in L[k-1][i]]
                L[k][i].extend(ll)
            if K <= cnt + len(L[k][i]):
                print(L[k][i][K - cnt - 1])
                exit()
            else:
                cnt += len(L[k][i])
        k += 1


if __name__ == "__main__":
    main()
