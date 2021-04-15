import random
# random.seed(777)

# 1 <= K <= N <= 5
N = random.randint(1, 5)
K = random.randint(1, N)
print(f"{N} {K}")

# for _ in range(N):
#     a = random.randint(-10, 10)
#     print(a)

A = " ".join(map(str, list(random.randint(-10, 10) for _ in range(N))))
print(A)
