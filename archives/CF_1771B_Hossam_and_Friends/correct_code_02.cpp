#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using LL = long long;

int n, m;

void solve() {
    std::cin >> n >> m;
    // mn[x] 初始只记录左端点恰好为 x 的陌生人对给出的右边界。
    std::vector<int> mn(n + 2, n);
    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        if (x > y) {
            std::swap(x, y);
        }
        mn[x] = std::min(mn[x], y - 1);
    }
    // 左端点为 i 的区间必须满足所有 x >= i 的陌生人对的限制。
    for (int i = n - 1; i >= 1; i--) {
        mn[i] = std::min(mn[i], mn[i + 1]);
    }
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        // 合法右端点为 [i, mn[i]]，单点区间也包含在内。
        res += mn[i] - i + 1;
    }
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
