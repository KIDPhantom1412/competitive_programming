#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

const int MOD = int(1e9) + 7;

int mod(int a) {
    return (a % MOD + MOD) % MOD;
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> range(n);
    int end = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        range[i] = {a, b};
        end = std::max(end, b);
    }
    std::vector<int> f(end + 1);
    f[0] = 1;
    fill_n(f.begin() + 1, m, 1); // 1 <= i < k 时只有全红一种方案
    for (int i = m; i <= end; i++) {
        // 末尾放 1 朵红花或 1 组 k 朵白花
        f[i] = mod(f[i - 1] + f[i - m]);
    }
    std::vector<int> ps(end + 1); // 前缀和，O(1) 回答区间询问
    for (int i = 1; i <= end; i++) {
        ps[i] = mod(ps[i - 1] + f[i]);
    }
    for (auto [a, b] : range) {
        std::cout << mod(ps[b] - ps[a - 1]) << '\n'; // 减法可能为负，需补正
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}
