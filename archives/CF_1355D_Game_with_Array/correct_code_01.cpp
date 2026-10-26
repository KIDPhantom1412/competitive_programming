#include <iostream>

void solve() {
    int n, s;
    std::cin >> n >> s;
    // S < 2N 时必败：前缀和模 S 只有 N 个不同余数，
    // 其中必有两个相差 K，Vasya 总能找到和为 K 或 S-K 的子数组
    if (s < n * 2) {
        std::cout << "NO" << '\n';
        return;
    }

    // 构造：N-1 个 2 和一个 S-2(N-1)（>= 2），取 K = 1
    // 所有元素 >= 2：和为 1 的子数组不存在；
    // 真子数组至多 S-2，整段为 S：和为 S-1 的子数组也不存在
    std::cout << "YES" << '\n';
    for (int i = 0; i < n - 1; i++) {
        std::cout << 2 << ' ';
    }
    std::cout << s - (n - 1) * 2 << '\n';
    std::cout << 1 << '\n';
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
