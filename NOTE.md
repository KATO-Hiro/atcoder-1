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
    - MLE
        - `vector` のメモリ解放： `A.clear(); A.shrink_to_fit();`
        - `map` のメモリ解放： `mp.clear();`
    - インタラクティブな問題と flush [[参考](https://rsk0315.hatenablog.com/entry/2020/05/09/170315)]
        - **`cin.tie(nullptr)` をコメントアウトするか `cout << endl` を使う**
        - インタラクティブな問題では出力の度に flush が必要であるため，
          `cin.tie(nullptr)` と `cout << '\n'` を両方使うと flush されず失敗する
            - `cin` の度に `cout` が flush され重いが `cin.tie(nullptr)` により回避 [[link](https://cpprefjp.github.io/reference/ios/basic_ios/tie.html)]
            - `endl` は「改行を出力」ではなく「改行を出力してバッファを flush する」 [[link](https://cpprefjp.github.io/reference/ostream/endl.html)]
    - 負数の剰余演算
        - C++ では `-3 % 2` の結果が `-1` になる (`1` ではなく)
        - パリティを求める場合，問題なければ絶対値にして剰余演算する

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
        - `string` を介した整数演算は重いため `10x + y` でループを書く [[abc198_d](https://atcoder.jp/contests/abc198/tasks/abc198_d)]
        - `unordered_xxx` は`平均 O(1)・最悪 O(N)` であり厳密に `O(1)` ではない
            - 配列でカウントすれば高速化できる (値の範囲が広ければ座圧)
        - 階乗で割る時は階乗の逆元を掛ける (そうしないと前計算の意味がない)
            - 階乗で割った場合 (663ms) [[Detail](https://atcoder.jp/contests/arc067/submissions/22733278)]
            - 逆元を掛けた場合 (51ms) [[Detail](https://atcoder.jp/contests/arc067/submissions/22733369)]
    - 誤差
        - 実数を扱う場合は誤差死の可能性あり
            - 整数で扱えるように式変形をする (分母を払う・ルートを外す) [[panasonic2020_c](https://atcoder.jp/contests/panasonic2020/tasks/panasonic2020_c)]
            - 少数が絡むのに許容誤差が無い場合は [[abc191_d](https://atcoder.jp/contests/abc191/tasks/abc191_d)]
            - (神頼み) `EPS` を刻む，`long double` を試す
        - `double` を使う場合は情報落ちに注意
            - `long double` で計算するか，実数計算をできるだけ避ける
              （算術平均なら割る直前まで整数で計算する [[ecr047_c](https://codeforces.com/contest/1009/problem/C)]）
    - ソート
        - やってない (半分全列挙など) or やってはいけない
        - 降順・昇順ミス (`SORT` ↔ `RSORT`)
    - 出力形式ミス
        - 構築系なら最初にサイズを出力するかどうか
        - 答えが複数ありうる場合に一意にするための条件を見落としている
    - 番兵
        - 数が足りない（2種類必要なケースもある．Lazy Faith とか）
        - 値が悪い (確実に役割を果たせる値を使用する．オーバーフローに注意)
    - 余事象を正しく計算できているか？ [[tenka1_2012_qualA_3](https://atcoder.jp/contests/tenka1-2012-qualA/tasks/tenka1_2012_qualA_3)]
    - `map` と `unordered_map` の混同
    - RMQ では負数があり得る場合は単位元に注意する
        - Range Maximum Query の場合は `-INF` が正しい (`0` はバグ) [[joi2015yo_f](https://atcoder.jp/contests/joi2015yo/tasks/joi2015yo_f)]

## 典型考察メモ

- 参考
    - [競技プログラミングにおける細かな話題まとめ (hamayanhamayan さん)](https://www.hamayanhamayan.com/entry/2017/06/07/234608)
    - [競技プログラミングの問題の解き方、そのマニュアル (kimiyuki さん)](https://kimiyuki.net/blog/2016/06/21/how-to-solve-problems-in-competitive-programming/)

- 基本方針
    1. 解法候補を直感的に列挙する
    1. 制約を確認する
        - 計算量がどこまで許容されるか見積もる
        - 制約から解法候補を列挙する
    1. サンプルを理解する
        - 図を書く
    1. 愚直解を考える
        - 愚直解で問題の本質 (難しさ) を理解する
        - 愚直解を高速化できないか検討する
        - (実装してランダムテストの準備をする)
    1. 条件を数式で整理する
        - 立式・式変形をする
    1. 条件を言い換える
        - 逆から考える
        - 余事象を考える
        - 主客転倒する（数え上げに限らない）
        - 単純化する
        - 同一視する
        - 相対的に考える
    1. どんな前処理が可能か考える ???
        - 累積和
        - 組み合わせ数 (DP)
        - 総和の作成可否 (DP)
    1. 問題パターン固有の典型考察を使う (後述)
    - 考察に詰まったら…
        - TODO

- 全般
    - 「必ず○○する□□をすべて求めよ（○○＝使う・通る等）」 [[abc161_e](https://atcoder.jp/contests/abc161/tasks/abc161_e)]
        - 各□□を一時的に無効にして成立するか評価することで各□□が必要か判定できる
    - 絶対値は ± で全探索を検討 [[abc100_d](https://atcoder.jp/contests/abc100/tasks/abc100_d)] [[abc178_e](https://atcoder.jp/contests/abc178/tasks/abc178_e)]
    - 周期性がある問題は「サイクル検出」「ダブリング」「拡張ユークリッド互除法」を考える [[abc030_d](https://atcoder.jp/contests/abc030/tasks/abc030_d)] [[past202004_m](https://atcoder.jp/contests/past202004-open/tasks/past202004_m)] [[abc186_e](https://atcoder.jp/contests/abc186/tasks/abc186_e)]
    - 順列は大小関係に着目する [[chokudai_S001_k](https://atcoder.jp/contests/chokudai_S001/tasks/chokudai_S001_k)] [[dp_t](https://atcoder.jp/contests/dp/tasks/dp_t)]
    - 回文は「中心」「両端」から考える [[abc197_f](https://atcoder.jp/contests/abc197/tasks/abc197_f)]
    - 実験が有効な場合がある（実験ゲー）[[arc108_d](https://atcoder.jp/contests/arc108/tasks/arc108_d)] [[arc107_e](https://atcoder.jp/contests/arc107/tasks/arc107_e)] [[arc072_b](https://atcoder.jp/contests/abc059/tasks/arc072_b)]

- 区間
    - 区間は「累積和」「セグメント木」「DP」「尺取り」で考える
        - DP: 区間 DP，耳 DP (状態遷移 DP ?)
    - 最適な区間を求める場合は「全探索」「区間 DP」 [[ecr039_d](https://codeforces.com/contest/946/problem/D)]
        - 両端から貪欲にやると内側を評価できないため最適解を逃す
    - 反転は端から貪欲 [蟻本] or 境界に着目 [[typical90_aw](https://atcoder.jp/contests/typical90/tasks/typical90_aw)]

- 二分探索
    - 単調性のある最小化/最大化問題は "決め打ち二分探索" [[link](https://betrue12.hateblo.jp/entry/2019/05/11/013403)]
    - 最適解を直接求めようとすると場合分けが多くて厳しい → 決め打ち二分探索 [[ecr053_c](https://codeforces.com/contest/1073/problem/C)]
    - 二分探索の判定問題の計算量を前計算で落として間に合わせる [[abc143_f](https://atcoder.jp/contests/abc143/tasks/abc143_f)]

- DP
    - 貰う DP は累積和で高速化できる可能性がある
    - 配る DP はインライン DP が使える可能性がある
    - unordered_set 配列より bool 配列の方が高速 (値の範囲が狭い場合) [[abc147_e](https://atcoder.jp/contests/abc147/tasks/abc147_e)]
    - 桁DP
        - `dp[先頭からi桁目][N未満確定フラグ][条件]` [[link](https://torus711.hatenablog.com/entry/20150423/1429794075)] [[link](https://www.hamayanhamayan.com/entry/2017/04/23/212728)]
        - 整数は `y = 10 * x + d` の繰り返しで計算可能 [[link](https://drken1215.hatenablog.com/entry/2020/04/23/194600)]
    - 状態を同一視する [[abc132_f](https://atcoder.jp/contests/abc132/tasks/abc132_f)]
    - 余りに着目する [[abc192_f](https://atcoder.jp/contests/abc192/tasks/abc192_f)] [[ecr061_e](https://codeforces.com/contest/1132/problem/E)]

- グラフ
    - 順序付きの集合は DAG で扱える（順序付けされているものを頂点に乗せる） [[abc139_e](https://atcoder.jp/contests/abc139/tasks/abc139_e)]
        - DAG は DP が使える（最短経路問題など）
    - 目的別に複数回のグラフ探索をする
        - 最短経路問題を 2 回解くケース [[abc143_e](https://atcoder.jp/contests/abc143/tasks/abc143_e)]
        - 探索順序を固定するために dfs を 2 回するケース [[abc199_d](https://atcoder.jp/contests/abc199/tasks/abc199_d)]
    - 閉路が存在しない場合 (森の場合) は下記が成立．数え上げ等で有用 [[abc173_f](https://atcoder.jp/contests/abc173/tasks/abc173_f)]
        - `頂点数 = 辺数 + 連結成分数`
    - 「奇数長サイクルを含まない」と「二部グラフである」は同値 [[code_festival_2017_qualb_c](https://atcoder.jp/contests/code-festival-2017-qualb/tasks/code_festival_2017_qualb_c)]
    - 超頂点を追加する [[abc184_e](https://atcoder.jp/contests/abc184/tasks/abc184_e)] [[ecr038_d](https://codeforces.com/contest/938/problem/D)]
    - 全域木を構築して木の問題に変換する [[joi2012ho5](https://atcoder.jp/contests/joi2012ho/tasks/joi2012ho5)]
    - 木に対するテクニック
        - クエリ先読み + dfs (行きがけ/帰りがけ) [[abc133_f](https://atcoder.jp/contests/abc133/tasks/abc133_f)] [[abc202_e](https://atcoder.jp/contests/abc202/tasks/abc202_e)]
        - 根付き木にして 木 DP [[abc138_d](https://atcoder.jp/contests/abc138/tasks/abc138_d)] [[abc187_e](https://atcoder.jp/contests/abc187/tasks/abc187_e)]
        - 根付き木にして LCA [[abc201_e](https://atcoder.jp/contests/abc201/tasks/abc201_e)]
            - `dist(u,v) = dist(r,u) + dist(r,v) - 2*dist(r,w)`  (`w = lca(u,v)`)
        - パスクエリと部分木クエリ
            - オイラーツアー (列の問題に変換して segtree)
            - HL 分解で殴る (AtCoder で想定解には多分ならない)
        - 各頂点を根としたクエリは全方位木 DP [[abc160_f](https://atcoder.jp/contests/abc160/tasks/abc160_f)]
        - 木全体の数え上げ・最大/最小は重心分解 [[yahoo_procon2018_final_c](https://atcoder.jp/contests/yahoo-procon2018-final-open/tasks/yahoo_procon2018_final_c)]
        - 深さ付き部分木クエリ (k-subtree query)
            - k-subtree minimum query: RMQ + ダブリング [[ecr033_f](https://codeforces.com/contest/893/problem/F)]
            - k-subtree add query: dfs 行きがけ/帰りがけ [[ecr054_e](https://codeforces.com/contest/1076/problem/E)]

- 貪欲
    - スケジューリングは前から貪欲に考える
    - 計算量解析すると実は貪欲で間に合うケースがある [[agc014_a](https://atcoder.jp/contests/agc014/tasks/agc014_a)] [[arc079_c](https://atcoder.jp/contests/arc079/tasks/arc079_c)]
    - 辞書順最小は前から貪欲 [[past202004_l](https://atcoder.jp/contests/past202004-open/tasks/past202004_l)]

- 数え上げ
    - **主客転倒テク**：すべての組み合わせのコスト総和を計算する場合，ある1つの組み合わせにおけるコストを要素毎に分解して，各要素が題意に与える寄与を独立に計算して数え上げる
    - 数え上げは DP の可能性が高い
    - 愚直な DP を考えてから高速化を考える（累積和など）

- 数学
    - 数学系の問題は**立式・式変形**をすることで解ける場合がある [[abc178_e](https://atcoder.jp/contests/abc178/tasks/abc178_e)] [[abc190_d](https://atcoder.jp/contests/abc190/tasks/abc190_d)]
    - `gcd, lcm` には結合法則が成り立つ e.g.) `gcd(a,gcd(b,c)) = gcd(gcd(a,b),c)`
        - 累積 gcd が有用な場合がある [[judge_update_202004_d](https://atcoder.jp/contests/judge-update-202004/tasks/judge_update_202004_d)]
    - `floor(A/B)` は `floor(A/B) = q, A = Bq + r (0≦r＜B)` で考察 [[abc165_d](https://atcoder.jp/contests/abc165/tasks/abc165_d)] [[arc111_a](https://atcoder.jp/contests/arc111/tasks/arc111_a)]
    - 偶奇性を利用する: `|x-y| ≡ x⊕y ≡ x+y (mod 2)` [[agc043_b](https://atcoder.jp/contests/agc043/tasks/agc043_b)]
    - 整数 `N` の `b` 進表記は `b ≦ √N` のとき 3 桁以上 `√N ＜ b` のとき 2 桁以下 [[arc060_b](https://atcoder.jp/contests/arc060/tasks/arc060_b)]
    - `gcd(a,b) = gcd(a-b,b) = gcd(a-b,a)  (a > b)` [[tweet](https://twitter.com/mts1104_ml/status/1377586281287282689)]

- ゲーム
    - 後退解析 + メモ化再帰 によるゲーム DP (状態数オーダーに注意)
    - Nimber
        - 状態数が多すぎて Nimber で解けない場合は必勝法を考える [[arc105_d](https://atcoder.jp/contests/arc105/tasks/arc105_d)]
    - 不変量
    - adhoc, O(1)
    - 考察ネタ
        - パリティを考える (操作回数のパリティ等)
        - 初期配置のパターンで場合分けする
        - 必勝法を探す
        - 終了局面に何か特徴がないか考える
        - 最終手段は実験 (ノート・愚直コード)

- 操作系
    - 不変量に着目する (全体の総和など)
    - 逆順を考える [[agc032_a](https://atcoder.jp/contests/agc032/tasks/agc032_a)] [[agc037_c](https://atcoder.jp/contests/agc037/tasks/agc037_c)]

- XOR
    - `0〜N` の XOR は `mod 4` で場合分け可能 [[link](https://www.hamayanhamayan.com/entry/2017/05/20/145021)] [[link](http://kyopro.hateblo.jp/entry/2019/05/22/054412)]
    - XOR は「繰り上がりのない足し算」と考える [[abc172_f](https://atcoder.jp/contests/abc172/tasks/abc172_f)]
        - `a + b = (a ⊕ b) + 2 * (a & b)`
            - `a + b ≧ (a ⊕ b)` が成立
            - `(a ⊕ b) & (a & b) = 0` が成立
                - `a & b` でビットが立つ桁は `a, b` いずれでもビットが立つ必要がある
                - その場合 `a ⊕ b` では必ずビットが立たない
    - `k` 番目のビットが `1` ⇔ `x mod 2^(k+1) ≧ 2^k`
    - XOR は桁ごとに考える [[arc092_b](https://atcoder.jp/contests/abc091/tasks/arc092_b)]

- フロー
    - 一般に成立する関係式 (独立集合 = 安定集合)
        - `|最大マッチング| + |最小辺カバー| = |頂点数|`  (孤立点のないグラフの場合)
        - `|最大独立集合| + |最小点カバー| = |頂点数|`
    - 二部グラフの最大独立集合は下記で求められる [[soundhound2018_c](https://atcoder.jp/contests/soundhound2018/tasks/soundhound2018_c)]
        - `|最大独立集合| = |頂点数| - |最大マッチング|`
          ( ∵ `|最大マッチング| = |最小点カバー|`)

## コマンド

- コンテスト開始時

    ```bash
    acc new abc123 ; cd abc123 ; code {a..f}/main.cpp
    ```

- プリコンパイル [[参考記事](https://kryozahiro.hateblo.jp/entry/20090921/1253534337)]
（オプションは普段使いと合わせる）

    ```bash
    # bits/stdc++.h
    cd /usr/include/x86_64-linux-gnu/c++/9/bits
    sudo /usr/bin/g++ -std=gnu++17 -Wall -Wextra -O2 -DONLINE_JUDGE -fsanitize=address -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC stdc++.h
    ```

- ランダムテスト

    1. `generate.py` に入力ケースのランダム生成を実装する
    1. `greedy.cpp` に愚直解を実装する（確実に正しい答えが得られるように）
    1. 下記を実施
    1. `[CTRL] + [C]` で完全停止

    ```bash
    # g++ main.cpp -o a.out
    g++ greedy.cpp -o b.out
    bash random_test.sh
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
