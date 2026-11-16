#include <iostream>
#include <vector>

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> p(n + 1);

    // 奇数余数组从小到大填，偶数余数组从大到小填。
    // 同一组里下标相差 k 的相邻两项差恰好是 +1 或 -1。
    int lo = 1, hi = n;
    for (int r = 1; r <= k; ++r) {
        for (int i = r; i <= n; i += k) {
            if (r % 2 == 1) {
                p[i] = lo++;
            } else {
                p[i] = hi--;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << p[i] << " \n"[i == n];
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
