#include <iostream>

void solve() {
    int n, a1 = 0, an = 0;
    std::cin >> n;
    // 只保存首尾元素，但仍需读完本组数据。
    for (int i = 1; i <= n; i++) {
        int a;
        std::cin >> a;
        if (i == 1) {
            a1 = a;
        } else if (i == n) {
            an = a;
        }
    }
    // 能删到一个元素的充要条件是首元素小于尾元素。
    if (a1 < an) {
        std::cout << "YES" << '\n';
    } else {
        std::cout << "NO" << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
