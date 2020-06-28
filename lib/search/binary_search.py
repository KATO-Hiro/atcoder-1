import sys

input = sys.stdin.readline


def is_ok(a, key, idx):
    if a[idx] >= key:
        return True
    else:
        return False


def binary_search(a, key):
    """Meguru type binary search"""
    ng = -1
    ok = len(a)

    while (abs(ok - ng) > 1):
        mid = (ok + ng) // 2
        if is_ok(a, key, mid):
            ok = mid
        else:
            ng = mid

    return ok


def main():
    A = [1, 14, 43, 51, 51, 51, 243, 419, 750, 910]
    print(f"{A = }")
    print(f"{binary_search(A, 51)  = }")
    print(f"{binary_search(A, 1)   = }")
    print(f"{binary_search(A, 910) = }")
    print(f"{binary_search(A, 52)  = }")
    print(f"{binary_search(A, 0)   = }")
    print(f"{binary_search(A, 911) = }")


if __name__ == "__main__":
    main()
