#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// --------------------------------------------------------
#define FOR(i,l,r) for (ll i = (l); i < (r); ++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(c) (c).begin(), (c).end()
using VS = vector<string>;
// --------------------------------------------------------


// References:
//   <https://en.wikipedia.org/wiki/Trie>
//   <https://algo-logic.info/trie-tree/>

/**
 * @brief トライ木 (Trie Tree)
 * 
 * @details "left-child right-sibling binary tree" (doubly chained tree)
 */
struct Trie {
    struct Node {
        char symbol;  // e.g.) a, b, c
        shared_ptr<Node> child = nullptr;  // child node
        shared_ptr<Node> next = nullptr;   // next sibling node
        bool exist = false;
        int size = 0;  // number of strings in descendant nodes
        vector<int> cnt;  // [NOTE] for agc047_b
        Node() : cnt(26,0) {}
        Node(const char& c) : symbol(c), cnt(26,0) {}
    };
    shared_ptr<Node> root;
    Trie() { root = make_shared<Node>(); }

    // 指定した文字列の挿入
    //   TODO: 辞書順で挿入
    void insert(const string& key) {
        assert(key != "");
        if (root->child == nullptr) { root->child = make_shared<Node>(key[0]); }
        root->size++;
        shared_ptr<Node> node = root->child;
        int N = key.size();
        for (int i = 0; i < N; i++) {
            while (true) {
                if (key[i] == node->symbol) { break; }
                if (node->next == nullptr) { node->next = make_shared<Node>(key[i]); }
                node = node->next;
            }
            node->size++;
            if (i == N-1) { break; }

            if (node->child == nullptr) { node->child = make_shared<Node>(key[i+1]); }
            node = node->child;
        }
        node->exist = true;
    }

    // 指定した文字列が含まれるか
    bool find(const string& key) {
        shared_ptr<Node> node = find_node(key);
        return (node == nullptr ? false : node->exist);
    }

    // 指定した prefix で始まる文字列が含まれるか
    bool starts_with(const string& prefix) { return (find_node(prefix) != nullptr); }

    // 指定した prefix で始まる文字列の個数
    int size(const string& prefix) {
        shared_ptr<Node> node = find_node(prefix);
        return (node == nullptr ? 0 : node->size);
    }

    // 指定した文字列に対応する shared_ptr<Node> を返す
    // 存在しなければ nullptr を返す
    shared_ptr<Node> find_node(const string& key) {
        if (key == "") { return root; }
        if (root->child == nullptr) { return nullptr; }
        shared_ptr<Node> node = root->child;
        int N = key.size();
        for (int i = 0; i < N; i++) {
            bool ok = false;
            while (true) {
                if (key[i] == node->symbol) { ok = true; break; }
                if (node->next == nullptr) { break; }
                node = node->next;
            }
            if (!ok) { return nullptr; }
            if (i == N-1) { break; }

            if (node->child == nullptr) { return nullptr; }
            node = node->child;
        }
        return node;
    }

    /** ---------- 以下は agc047_b 向けの機能 ---------- **/
    void build() {
        auto rec = [&](auto self, const shared_ptr<Node>& parent) -> void {
            shared_ptr<Node> node = parent->child;
            while (node != nullptr) {
                if (node->child != nullptr) {
                    self(self, node);
                    for (char c = 'a'; c <= 'z'; c++) {
                        parent->cnt[c-'a'] += (c == node->symbol ? node->size : node->cnt[c-'a']);
                    }
                } else {
                    if (node->exist) { parent->cnt[node->symbol-'a']++; }
                }
                node = node->next;
            }
        };
        assert(root->child != nullptr);
        rec(rec, root);
    }

    // prefix を持ち suffix に c を含む文字列の個数の連想配列
    vector<int> count(const string& prefix) {
        shared_ptr<Node> node = find_node(prefix);
        return (node == nullptr ? vector<int>() : node->cnt);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(15);

    ll N; cin >> N;
    VS S(N); REP(i,N) cin >> S[i];

    Trie trie;
    REP(i,N) {
        reverse(ALL(S[i]));
        trie.insert(S[i]);
    }
    trie.build();

    ll ans = 0;
    REP(i,N) {
        ll k = S[i].size();
        auto cnt = trie.count(S[i].substr(0,k-1));
        ans += cnt[S[i][k-1]-'a'] - 1;
    }
    cout << ans << endl;

    return 0;
}
// Verify: https://atcoder.jp/contests/agc047/tasks/agc047_b
