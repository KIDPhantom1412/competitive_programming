#include <algorithm>
#include <iostream>
#include <vector>

using LL = long long;

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<LL> ps(n + 1);    // 前缀和
    std::vector<int> cnt1(n + 1); // 前缀 1 的个数
    for (int i = 1; i <= n; i++) {
        int a;
        std::cin >> a;
        ps[i] = ps[i - 1] + a;
        cnt1[i] = cnt1[i - 1] + (a == 1);
    }

    while (q--) {
        int l, r;
        std::cin >> l >> r;
        LL sum = ps[r] - ps[l - 1];
        int ones = cnt1[r] - cnt1[l - 1];
        // 每段最小代价：a_i = 1 处 b_i 至少为 2，其余处 b_i 至少为 1
        LL least = ones + (r - l + 1);
        if (l == r || sum < least) {
            std::cout << "NO" << '\n';
        } else {
            std::cout << "YES" << '\n';
        }
    }
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
