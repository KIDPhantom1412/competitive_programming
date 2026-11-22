#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }

    // n = 1 时没有长度 n-1 的区间，三次都操作 [1,1]：先清零，再补两次 0
    if (n == 1) {
        for (int i = 0; i < 3; i++) {
            std::cout << 1 << ' ' << 1 << '\n';
            std::cout << (i == 0 ? -A[1] : 0) << '\n';
        }
        return;
    }

    // 操作 1：[1,1] 加 -a1，长度 1 任意整数合法
    std::cout << 1 << ' ' << 1 << '\n';
    std::cout << -A[1] << '\n';

    // 操作 2：[1,n] 长度 n，a1 加 0，i>=2 加 -n*a_i（n 的倍数），使 a_i 变为 (1-n)*a_i
    std::cout << 1 << ' ' << n << '\n';
    std::cout << 0 << ' ';
    for (int i = 2; i <= n; i++) {
        std::cout << int64_t(-n) * A[i] << ' '; // 乘法用 int64_t 防溢出
    }
    std::cout << '\n';

    // 操作 3：[2,n] 长度 n-1，i>=2 加 (n-1)*a_i，恰好把 (1-n)*a_i 抵消为 0
    std::cout << 2 << ' ' << n << '\n';
    for (int i = 2; i <= n; i++) {
        std::cout << int64_t(n - 1) * A[i] << ' ';
    }
    std::cout << '\n';
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
