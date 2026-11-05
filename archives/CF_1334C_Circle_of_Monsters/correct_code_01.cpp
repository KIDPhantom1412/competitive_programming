#include <algorithm>
#include <iostream>
#include <vector>

using LL = long long;

const LL INF = LL(1e12) + 10;

LL mod(LL a, LL m) {
    return (a % m + m) % m;
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<LL> A(n), B(n);
    for (int i = 0; i < n; i++) {
        std::cin >> A[i] >> B[i];
    }

    LL res = 0;
    LL mn = INF;
    for (int i = 0; i < n; i++) {
        // 上一只爆炸最多抵掉 b_{i-1}，这只至少还要自己补的子弹。
        LL left = std::max(0LL, A[i] - B[mod(i - 1, n)]);
        res += left;
        // 放弃这只的爆炸减免时，多付的是 min(a_i, b_{i-1})。
        mn = std::min(mn, A[i] - left);
    }
    res += mn;
    std::cout << res << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
