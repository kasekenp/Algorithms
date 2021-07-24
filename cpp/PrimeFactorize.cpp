#include <bits/stdc++.h>
using namespace std;

vector<pair<long long, long long>> prime_factorize(long long n) {
    vector<pair<long long, long long>> res;
    for (long long a = 2; a * a <= n; a++) {
        if (n % a != 0) continue;
        long long ex = 0;
        while (n % a == 0) {
            ex++;
            n /= a;
        }
        res.push_back({a, ex});
    }
    if (n != 1) res.push_back({n, 1});
    return res;
}

int main() {
    long long n;
    cin >> n;
    const auto &res = prime_factorize(n);
    cout << n << ":";
    for (auto p : res) {
        for (int i = 0; i < p.second; ++i) cout << " " << p.first;
    }
    cout << endl;
}