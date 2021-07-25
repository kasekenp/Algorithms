#include <bits/stdc++.h>
using namespace std;

vector<int> sort_chars(string &s) {
    vector<int> res(s.size());
    map<int, int> cnt;
    for (const auto c : s) {
        cnt[c]++;
    }
    auto prev = cnt.begin();
    for (auto it = cnt.begin(); it != cnt.end(); it++) {
        if (it == cnt.begin()) continue;
        it->second += prev->second;
        prev = it;
    }
    for (int i = (int)s.size() - 1; i >= 0; i--) {
        cnt[s.at(i)]--;
        res.at(cnt[s.at(i)]) = i;
    }
    return res;
}

vector<int> compute_classes(string &s, vector<int> &order) {
    vector<int> res(s.size(), 0);
    for (int i = 1; i < (int)order.size(); i++) {
        const int inc = s.at(order.at(i)) != s.at(order.at(i - 1));
        res.at(order.at(i)) = res.at(order.at(i - 1)) + inc;
    }
    return res;
}

vector<int> sort_doubled(string &s, int l, vector<int> &order,
                         vector<int> &clazz) {
    const int n = s.size();
    vector<int> new_order(n), cnt(n);
    for (int i = 0; i < n; i++) {
        cnt.at(clazz.at(i))++;
    }
    for (int i = 1; i < n; i++) {
        cnt.at(i) += cnt.at(i - 1);
    }
    for (int i = n - 1; i >= 0; i--) {
        const auto start = (order.at(i) - l + n) % n;
        const auto cl = clazz.at(start);
        cnt.at(cl)--;
        new_order.at(cnt.at(cl)) = start;
    }
    return new_order;
}

vector<int> update_classes(vector<int> &new_order, vector<int> &clazz, int l) {
    const int n = new_order.size();
    vector<int> new_class(n, 0);
    auto prev = new_order.at(0);
    auto mid_prev = (prev + l) % n;
    for (int i = 1; i < n; i++) {
        const auto cur = new_order.at(i);
        const auto mid = (cur + l) % n;
        const int inc = clazz.at(cur) != clazz.at(prev) ||
                        clazz.at(mid) != clazz.at(mid_prev);
        new_class.at(cur) = new_class.at(prev) + inc;
        prev = cur, mid_prev = mid;
    }
    return new_class;
}

vector<int> suffix_array(string &s) {
    auto order = sort_chars(s);
    auto clazz = compute_classes(s, order);
    for (int l = 1; l < (int)s.size(); l *= 2) {
        order = sort_doubled(s, l, order, clazz);
        clazz = update_classes(order, clazz, l);
    }
    return order;
}

int main() {
    string str;
    cin >> str;
    const auto res = suffix_array(str);
    for (const auto n : res) {
        cout << n << ' ';
    }
    cout << endl;
}