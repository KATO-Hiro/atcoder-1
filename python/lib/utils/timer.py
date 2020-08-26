# Timer
import time  # NOQA
from contextlib import contextmanager  # NOQA
@contextmanager
def timer(name):
    start_time = time.perf_counter()
    yield
    print(f'[{name}] done in {1000 * (time.perf_counter() - start_time):.0f} [ms]')


if __name__ == "__main__":
    N = 10 ** 7
    with timer("for-loop"):
        for i in range(N):
            a = i + 1
