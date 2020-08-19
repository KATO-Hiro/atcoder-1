# 精進ノート

## 典型メモ

- 方針
  - 正攻法でダメなら貪欲法を検討（計算量を見積もる）
  - 愚直実装で実験して解法の糸口を掴む

- 全般
  - 組み合わせ問題は部分問題に分割
  - 単調性のある最小化/最大化問題は "決め打ち二分探索" [[link](https://betrue12.hateblo.jp/entry/2019/05/11/013403)]
  - 区間は「累積和」「セグメント木」「DP」で考える
  - 条件を満たす区間の「最大/最小の長さ」「数え上げ」は尺取り法

- XOR
  - `0〜N` の XOR は `mod 4` で場合分け可能 [[link](https://www.hamayanhamayan.com/entry/2017/05/20/145021)] [[link](http://kyopro.hateblo.jp/entry/2019/05/22/054412)]

- 桁DP
  - `dp[先頭からi桁目][N未満確定フラグ][条件]` [[link](https://torus711.hatenablog.com/entry/20150423/1429794075)] [[link](https://www.hamayanhamayan.com/entry/2017/04/23/212728)]
  - 整数は `y = 10 * x + d` の繰り返しで計算可能 [[link](https://drken1215.hatenablog.com/entry/2020/04/23/194600)]

## Numba (0.48.0)

主に Numba くんの悪口

- **Numba のここがすごい**
  - Python を手軽に高速化できる！

- **Numba のここがダメ**
  - エラーメッセージが死ぬほど分かりにくい
  - `TypedList` の配列アクセスが激遅（隣接リストが絶望的）
  - `collections` が使えない
    - `Counter`, `deque`
  - `itertools` が使えない
    - `combinations`, `combinations_with_replacement`, `permutations`, `product`
  - `pow` が使えない
  - `set()` が使えない
