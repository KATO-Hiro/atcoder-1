# 精進ノート

## デバッグメモ

- C++ 仕様と実装全般
    - スコープ内外で名前衝突
        - グローバルとローカル
        - ある関数直下とその中の `{}` の中
    - オーバーフロー
        - `stoi` → `stoll`
    - iterator 仕様理解ミス
        - `lower_bound`, `upper_bound`
        - `rbegin`, `rend`
        - iterator 引き算順序：
            - `A.end() - lower_bound(ALL(A),a)  // a 以上の要素数 (end が先！)`
    - 使用変数ミス
        - `{N,M,K}`, `{i,j}`, `{i,1}`, `{i1,i2,j1,j2}` などの混同
        - `A[i]` → `A[B[i]]` (id 変数の未使用)
    - ループ範囲ミス
        - `FOR(i,M)` ↔ `REP(i,N)`
        - `FOR(i,1,N+1)` ↔ `REP(i,N)`
        - `FOR(i,1,N)` → `FOR(i,1,N+1)`
        - `REP(i,N)` → `REP(i,1<<N)`
    - 符号ミス（マイナスつけ忘れ，引き算順序ミスなど）
    - multiset
        - `set` ↔ `multiset`
        - 1要素だけ削除するなら `S.erase(S.find(x))`
    - 横着ミス
        - `while (++i < N && A[i] == B[i])` → `while (++i < N && A[i] == B[i]) {}`
            - 明示的に `{}` を書かないと次行以降がループする
- 競プロ系
    - 誤読
        - 有向グラフ・無向グラフのミス
        - **答えが一意に定まらない場合は真っ先に誤読を疑う** [[abc192_d](https://atcoder.jp/contests/abc192/tasks/abc192_d)]
        - 個数と種類数を混同している
    - 初期化ミス (DP, カウント数など)
    - オーバーフロー
        - 二分探索： `mid` を掛け算に使っている場合 → 初期値・評価式を工夫する
    - コーナーケース
        - `{0,1,2}` の場合 (下限付近)
        - `A == B` の場合 (2変数が同値)
        - 偶奇性 (偶数と奇数で場合分けすべき)
    - TLE
        - `while` 文に `break` がない，到達できてない
        - 複数の配列の参照分岐で毎回生成してしまっている (`&` が抜けてる)  
          `auto A = hoge ? A1 : A2` → `auto& A = hoge ? A1 : A2`
        - `debug` 文を削除していない（`O(N)` はかなり重い）
        - `ld (long double)` は計算が重く，`double` で十分な判定条件なら `ld` は使わない
    - 誤差
        - 実数を扱う場合は誤差死の可能性あり
            - 整数で扱えるように，式変形したり `10^x` を掛けるなどする
            - (神頼み) `EPS` を刻む，`long double` を試す
    - ソート
        - やってない (半分全列挙など) or やってはいけない
        - 降順・昇順ミス (`SORT` ↔ `RSORT`)
    - 出力形式ミス
        - 構築系なら最初にサイズを出力するかどうか
        - 答えが複数ありうる場合に一意にするための条件を見落としている
    - 番兵
        - 数が足りない（2種類必要なケースもある．Lazy Faith とか）
        - 値が悪い (確実に役割を果たせる値を使用する．オーバーフローに注意)

## 典型考察メモ

- 参考
    - [競技プログラミングにおける細かな話題まとめ (hamayanhamayan さん)](https://www.hamayanhamayan.com/entry/2017/06/07/234608)

- 全般
    - 単調性のある最小化/最大化問題は "決め打ち二分探索" [[link](https://betrue12.hateblo.jp/entry/2019/05/11/013403)]
    - 区間は「累積和」「セグメント木」「DP」「尺取り」で考える
    - 「必ず○○する□□をすべて求めよ（○○＝使う・通る等）」 [[abc161_e](https://atcoder.jp/contests/abc161/tasks/abc161_e)]
        - 各□□を一時的に無効にして成立するか評価することで各□□が必要か判定できる
    - 絶対値は ± で全探索を検討 [[abc100_d](https://atcoder.jp/contests/abc100/tasks/abc100_d)] [[abc178_e](https://atcoder.jp/contests/abc178/tasks/abc178_e)]
    - 周期性がある問題は「サイクル検出」「ダブリング」「拡張ユークリッド互除法」を考える [[abc030_d](https://atcoder.jp/contests/abc030/tasks/abc030_d)] [[past202004_m](https://atcoder.jp/contests/past202004-open/tasks/past202004_m)] [[abc186_e](https://atcoder.jp/contests/abc186/tasks/abc186_e)]
    - 順列は大小関係に着目する [[chokudai_S001_k](https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_k)] [[dp_t](https://atcoder.jp/contests/dp/tasks/dp_t)]

- DP
    - 貰う DP は累積和で高速化できる可能性がある
    - 配る DP はインライン DP が使える可能性がある
    - unordered_set 配列より bool 配列の方が高速 (値の範囲が狭い場合) [[abc147_e](https://atcoder.jp/contests/abc147/tasks/abc147_e)]
    - 桁DP
        - `dp[先頭からi桁目][N未満確定フラグ][条件]` [[link](https://torus711.hatenablog.com/entry/20150423/1429794075)] [[link](https://www.hamayanhamayan.com/entry/2017/04/23/212728)]
        - 整数は `y = 10 * x + d` の繰り返しで計算可能 [[link](https://drken1215.hatenablog.com/entry/2020/04/23/194600)]

- グラフ
    - 順序付きの集合は DAG で扱える（順序付けされているものを頂点に乗せる） [[abc139_e](https://atcoder.jp/contests/abc139/tasks/abc139_e)]
        - DAG は DP が使える（最短経路問題など）
    - 最短経路問題などを解いた結果を用いて別のグラフを構築して解くケースがある [[abc143_e](https://atcoder.jp/contests/abc143/tasks/abc143_e)]
    - 条件式がたくさんあり芋づる式に確定していく問題はグラフで考える
    - 閉路が存在しない場合 (森の場合) は下記が成立．数え上げ等で有用 [[abc173_f](https://atcoder.jp/contests/abc173/tasks/abc173_f)]
        - `頂点数 = 辺数 + 連結成分数`
    - 「奇数長サイクルを含まない」と「二部グラフである」は同値 [[code_festival_2017_qualb_c](https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_c)]

- 貪欲
    - スケジューリングは前から貪欲に考える
    - 計算量解析すると実は貪欲で間に合うケースがある [[agc014_a](https://atcoder.jp/contests/agc014/tasks/agc014_a)]
    - 辞書順最小は前から貪欲 [[past202004_l](https://atcoder.jp/contests/past202004-open/tasks/past202004_l)]

- 数え上げ
    - **主客転倒テク**：すべての組み合わせのコスト総和を計算する場合，ある1つの組み合わせにおけるコストを要素毎に分解して，各要素が題意に与える寄与を独立に計算して数え上げる
    - 数え上げは DP の可能性が高い
    - 愚直な DP を考えてから高速化を考える（累積和など）

- 数学
    - 数学系の問題は**立式・式変形**をすることで解ける場合がある [[abc178_e](https://atcoder.jp/contests/abc178/tasks/abc178_e)] [[abc190_d](https://atcoder.jp/contests/abc190/tasks/abc190_d)]
    - `gcd, lcm` には結合法則が成り立つ e.g.) `gcd(a,gcd(b,c)) = gcd(gcd(a,b),c)`
        - 累積 gcd が有用な場合がある
    - `floor(A/B)` は `A = Bq + r (0≦r＜B), floor(A/B) = q` を利用 [[abc165_d](https://atcoder.jp/contests/abc165/tasks/abc165_d)] [[arc111_a](https://atcoder.jp/contests/arc111/tasks/arc111_a)]
    - 偶奇性を利用する: `|x-y| ≡ x⊕y ≡ x+y (mod 2)` [[agc043_b](https://atcoder.jp/contests/agc043/tasks/agc043_b)]

- ゲーム
    - 後退解析 + メモ化再帰 によるゲーム DP (状態数オーダーに注意)
    - Grundy 数
    - 不変量
    - adhoc, O(1)
    - 考察ネタ
        - パリティを考える (操作回数のパリティ等)
        - 初期配置のパターンで場合分けする
        - 勝利確定パターンを探す
        - 終了局面に何か特徴がないか考える
        - 最終手段は実験 (ノート・愚直コード)

- 操作系
    - 不変量に着目する (全体の総和など)
    - 逆順を考える [[agc032_a](https://atcoder.jp/contests/agc032/tasks/agc032_a)] [[agc037_c](https://atcoder.jp/contests/agc037/tasks/agc037_c)]

- XOR
    - `0〜N` の XOR は `mod 4` で場合分け可能 [[link](https://www.hamayanhamayan.com/entry/2017/05/20/145021)] [[link](http://kyopro.hateblo.jp/entry/2019/05/22/054412)]

## コマンド

コンテスト開始時

```bash
acc new abc123 ; cd abc123 ; code {a..f}/main.cpp
```

プリコンパイル [[参考記事](https://kryozahiro.hateblo.jp/entry/20090921/1253534337)]
（オプションは普段遣いと合わせる）

```bash
# bits/stdc++.h
cd /usr/include/x86_64-linux-gnu/c++/9/bits
sudo /usr/bin/g++ -std=gnu++17 -Wall -Wextra -O2 -DONLINE_JUDGE -fsanitize=address -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC stdc++.h
```

---

以下は一応残してるだけ

## C++ (GCC 9.2.1)

- `next_permutation()` は対象が昇順ソート済みでないと順列が全列挙されない
- `double` 型の値を出力する際は表示桁数を増やさないと精度低下する [[link](https://atcoder.jp/contests/apg4b/tasks/APG4b_y)]
- `string` 型は終端文字 `'\0'` が入っているため，range-for などで注意が必要
- `boost/multiprecision` を使えば C++ でも多倍長整数が使える

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
