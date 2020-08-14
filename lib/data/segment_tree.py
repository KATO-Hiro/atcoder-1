import sys

input = sys.stdin.readline


class SegmentTree:
    """Segment Tree class.

    Args:
        N (int): Number of elements
        X (list[int]): List for initialization
        func (callable): Function for interval.
        init_v (int): Initial value that does not affect `func`.
            For example, specify INF when `func = min`.

    References:
        <https://en.wikipedia.org/wiki/Segment_tree>
    """
    def __init__(self, N, X, func, init_v):
        self.N = N
        self.func = func
        self.init_v = init_v
        self.__build(X)

    def __build(self, X):
        # Initialize all nodes
        self.node = [self.init_v] * (2 * self.N)  # 1-based index

        # Elementary intervals are stored
        for i, x in enumerate(X, self.N):
            self.node[i] = x

        # The internal nodes correspond to intervals that are the union of elementary intervals
        for i in range(self.N - 1, 0, -1):
            self.node[i] = self.func(self.node[i << 1], self.node[i << 1 | 1])

    def update(self, i, x):
        """Update the i-th node value to x.

        Args:
            i (int): index (1-based index)
            x (int): udpate value
        """
        i += self.N - 1
        self.node[i] = x
        while i > 1:
            i >>= 1
            self.node[i] = self.func(self.node[i << 1], self.node[i << 1 | 1])

    def query(self, l, r):
        """Query for right half-open interval [l, r).

        Args:
            l (int): index (1-based index)
            r (int): index (1-based index)
        """
        dst_l = self.init_v
        dst_r = self.init_v
        l += self.N - 1
        r += self.N - 1
        while l < r:
            if l & 1:
                dst_l = self.func(dst_l, self.node[l])
                l += 1
            if r & 1:
                r -= 1
                dst_r = self.func(self.node[r], dst_r)
            l >>= 1
            r >>= 1
        return self.func(dst_l, dst_r)


def main():
    N, Q = map(int, input().split())
    a = [2 ** 31 - 1] * N

    st = SegmentTree(N, a, func=min, init_v=float("inf"))

    ans = []
    for _ in range(Q):
        com, x, y = map(int, input().split())
        if com == 0:
            # update
            x += 1  # For AOJ input type (0-based index)
            st.update(x, y)
        else:
            # find
            x += 1  # For AOJ input type (0-based index)
            y += 1  # For AOJ input type (0-based index)
            ans.append(st.query(x, y + 1))

    print("\n".join(map(str, ans)))


if __name__ == "__main__":
    main()

"""
<http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A>

Example:
<input>
3 5
0 0 1
0 1 2
0 2 3
1 0 2
1 1 2
<output>
1
2
"""
