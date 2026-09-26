#include <iostream>

using LL = long long;

void solve() {
    int n, a, b;
    std::cin >> n >> a >> b;
    // a == 1 时乘 a 不改变数值，只能反复加 b；继续 i *= a 会死循环
    if (a == 1) {
        if ((n - 1) % b == 0) {
            std::cout << "Yes" << '\n';
        } else {
            std::cout << "No" << '\n';
        }
        return;
    }

    // 先乘出 a^k，再只在末尾加 b：需要 a^k <= n 且 a^k ≡ n (mod b)
    int target = n % b;
    for (LL i = 1; i <= n; i *= a) {
        if (i % b == target) {
            std::cout << "Yes" << '\n';
            return;
        }
    }
    std::cout << "No" << '\n';
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
