#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;


void ReplaceAll(string &str, const string &from, const string &to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return;
}


// Verify: https://atcoder.jp/contests/tenka1-2012-qualC/tasks/tenka1_2012_10
int main() {
    vector<char> royal = { '1', 'J', 'Q', 'K', 'A' };
    map<char,int> cnt = {{'S', 0}, {'H', 0}, {'D', 0}, {'C', 0}};

    string s;
    cin >> s;
    // 10 --> 1)
    ReplaceAll(s, "10", "1");
    int N = s.size();
    int last = 0;
    char royal_mark;
    rep(i, N) {
        for (char number : royal) {
            if (s[i] == number) {
                cnt[s[i - 1]]++;
                break;
            }
        }
        for (auto c : cnt) {
            if (c.second == 5) {
                royal_mark = c.first;
                last = i;
                break;
            }
        }
        if (last != 0) break;
    }
    s = s.substr(0, last + 1);
    for (char number : royal) {
        string card = "";
        card += royal_mark;
        card += number;
        s = s.erase(s.find(card), 2);
    }
    // 10 --> 1)
    ReplaceAll(s, "1", "10");

    if (s.size() == 0) {
        cout << 0 << endl;
    } else {
        cout << s << endl;
    }

    return 0;
}