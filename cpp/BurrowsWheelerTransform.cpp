#include <bits/stdc++.h>
using namespace std;

string invert_bwt(string &last) {
    string first = "";
    for (const auto c : last) first += c;
    sort(first.begin(), first.end());
    unordered_map<char, vector<int>> first_idx;
    for (int i = 0; i < (int)first.size(); i++) {
        first_idx[first.at(i)].push_back(i);
    }
    unordered_map<char, int> last_cnt;
    vector<int> last_ith(last.size(), 0);
    for (int i = 0; i < (int)last.size(); i++) {
        last_cnt[last.at(i)]++;
        last_ith.at(i) = last_cnt[last.at(i)] - 1;
    }
    string ret = "$";
    int i = 0;
    while (last.at(i) != '$') {
        ret.push_back(last.at(i));
        const auto ith = last_ith.at(i);
        i = first_idx[last.at(i)].at(ith);
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

string bwt(string &s) {
    vector<string> mat;
    const int n = s.size();
    for (int i = 0; i < n; i++) {
        string tmp = "";
        for (int j = 0; j < n; j++) {
            tmp += s.at((i + j) % n);
        }
        mat.push_back(tmp);
    }
    sort(mat.begin(), mat.end());
    string ret = "";
    for (int i = 0; i < (int)mat.size(); i++) {
        ret += mat.at(i).at(n - 1);
    }
    return ret;
}

int main() {
    string s;
    cin >> s;
    cout << invert_bwt(s) << endl;
}