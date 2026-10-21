#include <algorithm>
#include <iostream>
#include <tuple>

// 构造三个和为 n、lcm <= n/2 的正整数
std::tuple<int, int, int> lcm3(int n) {
    if (n % 2) {
        // 奇数：(n-1)/2 + (n-1)/2 + 1，lcm = (n-1)/2 < n/2
        return {n / 2, n / 2, 1};
    } else if (n % 4) {
        // n ≡ 2 (mod 4)：n/2 为奇数，n/2-1 为偶数，lcm = n/2-1 < n/2
        return {n / 2 - 1, n / 2 - 1, 2};
    }
    // n ≡ 0 (mod 4)：lcm = n/2，恰好取到上界
    return {n / 4, n / 4, n / 2};
}

void solve() {
    int n, k;
    std::cin >> n >> k;
    // 先在 n-k+3 上凑出三元组，剩余 k-3 个位置全部补 1（不影响 lcm）
    auto [a, b, c] = lcm3(n - k + 3);
    std::cout << a << ' ' << b << ' ' << c << ' ';
    while ((k--) > 3) {
        std::cout << 1 << ' ';
    }
    std::cout << '\n';
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
