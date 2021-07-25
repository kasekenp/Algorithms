#include <bits/stdc++.h>
using namespace std;

vector<int> prefix_func(string &p) {
    vector<int> s(p.size(), 0);
    int border = 0;
    for (int i = 1; i < (int)p.size(); i++) {
        while (border > 0 && p.at(i) != p.at(border)) {
            border = s.at(border - 1);
        }
        if (p.at(i) == p.at(border)) {
            border++;
        }
        s.at(i) = border;
    }
    return s;
}

vector<int> kmp(string &str, string &p) {
    string t = p + '$' + str;
    const auto s = prefix_func(t);
    vector<int> res;
    const int n = p.size();
    for (int i = n; i < (int)s.size(); i++) {
        if (s.at(i) == n) {
            res.push_back(i - 2 * n);
        }
    }
    return res;
}

int main() {
    string str, pat;
    cin >> pat >> str;
    const auto res = kmp(str, pat);
    for (const auto n : res) {
        cout << n << ' ';
    }
    cout << endl;
}