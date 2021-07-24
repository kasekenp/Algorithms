#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1000000007;

long long pow_mod(long long x, long long n) {
    if (n == 0) return 1;
    long long res = 1;
    res = pow_mod(x, n / 2);
    if (n % 2 == 0) {
        res = (res * res) % MOD;
    } else {
        res = (((res * res) % MOD) * x) % MOD;
    }
    return res;
}

int main() {
    long long M, N;
    cin >> M >> N;
    cout << pow_mod(M, N) << endl;
}