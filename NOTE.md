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

## C++ (GCC 9.2.1)

- `next_permutation()` は対象が昇順ソート済みでないと順列が全列挙されない
- `double` 型の値を出力する際は表示桁数を増やさないと精度低下する [link](https://atcoder.jp/contests/apg4b/tasks/APG4b_y)
- `string` 型は終端文字 `'\0'` が入っているため，range-for などで注意が必要

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

## 自己分析

- 2020/9/5(土)更新
- C++
- 水色レベル感で熟練度を自己評価

### アルゴリズム

|大分類                |小分類                |熟練度    |ライブラリ|備考|
|:--------------------:|:---------------------|:--------:|:--------:|:--:|
|全探索                |再帰関数              |■■□□□|:white_check_mark:||
|全探索                |スタック              |■■■■□|:white_check_mark:||
|全探索                |キュー                |■■■■□|:white_check_mark:||
|全探索                |深さ優先探索 (DFS)    |■■■■□|:heavy_check_mark:||
|全探索                |幅優先探索 (BFS)      |■■■■□|:heavy_check_mark:||
|全探索                |0-1 BFS               |□□□□□|:white_check_mark:||
|全探索                |順列全探索            |■■□□□|:white_check_mark:||
|全探索                |bit全探索             |■■■□□|:heavy_check_mark:||
|全探索                |半分全列挙            |□□□□□|:white_check_mark:||
|二分探索              |ソート整数列          |■■■□□|:white_check_mark:||
|二分探索              |ソート実数列          |■■□□□|:white_check_mark:||
|二分探索              |決め打ち二分探索      |■■□□□|:white_check_mark:||
|貪欲法                |                      |□□□□□|:white_check_mark:||
|グラフ                |ダイクストラ法        |■■■□□|:heavy_check_mark:||
|グラフ                |ワーシャルフロイド法  |■■■■□|:heavy_check_mark:||
|グラフ                |クラスカル法          |■□□□□|:white_check_mark:||
|グラフ                |ベルマンフォード法    |□□□□□|:white_check_mark:||
|グラフ                |拡張ダイクストラ法    |□□□□□|:white_check_mark:||
|木                    |                      |□□□□□|:white_check_mark:||
|整数論                |最小公倍数 (LCM)      |■■■■■|:heavy_check_mark:||
|整数論                |最大公約数 (GCD)      |■■■■■|:heavy_check_mark:||
|整数論                |ユークリッドの互除法  |■■■□□|:white_check_mark:||
|整数論                |拡張ユークリッドの互除法 |□□□□□|:white_check_mark:||
|整数論                |素数判定 (試し割り法) |■■■■■|:heavy_check_mark:||
|整数論                |素因数分解 (試し割り法) |■■■■■|:heavy_check_mark:||
|整数論                |素因数分解 (osa_k法)  |□□□□□|:white_check_mark:|[[link](https://qiita.com/rsk0315_h4x/items/ff3b542a4468679fb409)]|
|整数論                |素数列挙 (エラトステネスの篩) |■■■□□|:heavy_check_mark:||
|整数論                |素数列挙 (エラトステネスの区間篩) |□□□□□|:white_check_mark:||
|整数論                |約数列挙              |■■■□□|:heavy_check_mark:||
|整数論                |べき乗 (繰り返し二乗法) |■■■■■|:heavy_check_mark:||
|整数論                |逆元                  |□□□□□|:white_check_mark:||
|整数論                |二項係数 (nCk) mod P  |■■■□□|:heavy_check_mark:||
|動的計画法 (DP)       |ナップサック          |■□□□□|:white_check_mark:||
|動的計画法 (DP)       |桁DP                  |■■□□□|:white_check_mark:||
|動的計画法 (DP)       |bit DP                |□□□□□|:white_check_mark:||
|動的計画法 (DP)       |連鎖行列積            |□□□□□|:white_check_mark:||
|動的計画法 (DP)       |最長共通部分列 (LCS)  |□□□□□|:white_check_mark:||
|動的計画法 (DP)       |最長増加部分列 (LIS)  |□□□□□|:white_check_mark:||
|累積和                |1次元                 |■■■□□|||
|累積和                |2次元                 |■□□□□|:white_check_mark:||
|累積和                |imos法 (1次元)        |■■□□□|:white_check_mark:||
|累積和                |imos法 (2次元)        |□□□□□|:white_check_mark:||
|計算幾何学            |                      |□□□□□|:white_check_mark:||
|未分類                |しゃくとり法          |■■□□□|:white_check_mark:||
|未分類                |ライツアウト          |□□□□□|:white_check_mark:||
|未分類                |弾性衝突              |□□□□□|:white_check_mark:||
|未分類                |座標圧縮              |□□□□□|:white_check_mark:||
|未分類                |行列累乗              |□□□□□|:white_check_mark:||
|未分類                |フロー                |□□□□□|:white_check_mark:||
|                      |                      |□□□□□|:white_check_mark:||
|                      |                      |□□□□□|:white_check_mark:||

### データ構造

|大分類                |小分類                |自己評価  |ライブラリ|備考|
|:--------------------:|:--------------------:|:--------:|:--------:|:--:|
|Union-Find            |                      |■■■□□|:heavy_check_mark:||
|Union-Find            |重み付き Union-Find   |□□□□□|:white_check_mark:||
|Union-Find            |永続 Union-Find       |□□□□□|:white_check_mark:||
|平衡二分木            |                      |■■■□□|||
|優先度付きキュー      |                      |■■■□□|||
|二分探索木            |                      |□□□□□|:white_check_mark:||
|セグメント木          |                      |■□□□□|:heavy_check_mark:||
|Binary Indexed Tree (BIT) |                  |□□□□□|:white_check_mark:||
|バケット法            |                      |□□□□□|:white_check_mark:||
|平方分割              |                      |□□□□□|:white_check_mark:||
|                      |                      |□□□□□|:white_check_mark:||
