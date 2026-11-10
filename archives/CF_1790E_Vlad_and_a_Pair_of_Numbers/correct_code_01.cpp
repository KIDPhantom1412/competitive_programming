#include <iostream>

void solve() {
    int x;
    std::cin >> x;
    int a = 0, b = 0;
    // a & b 应为 x/2：把 x>>1 的每一位同时放到 a 和 b 上
    for (int i = 0; i < 30; i++) {
        if ((x >> 1) >> i & 1) {
            a |= 1 << i;
            b |= 1 << i;
        }
    }
    for (int i = 0; i < 30; i++) {
        if (x >> i & 1) {
            // 这一位属于 a⊕b，不能已经出现在 a&b 里
            if ((a >> i & 1) || (b >> i & 1)) {
                std::cout << -1 << '\n';
                return;
            }
            a |= 1 << i;
        } else if ((a >> i & 1) ^ (b >> i & 1)) {
            // 异或为 0 的位，a 和 b 必须相同
            std::cout << -1 << '\n';
            return;
        }
    }
    // x 为奇数时最低位只进了 a，a+b 为奇数，不可能等于 2x
    if ((a + b) % 2) {
        std::cout << -1 << '\n';
        return;
    }
    std::cout << a << ' ' << b << '\n';
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
