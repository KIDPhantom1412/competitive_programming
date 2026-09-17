#include <iostream>

int n, k;

int bitLength(int x) {
    for (int i = 0;; i++) {
        if ((x >> i) == 0) {
            return i;
        }
    }
    return -1;
}

void solve() {
    std::cin >> n >> k;
    int t = n ^ k; // 前 n-1 个前缀 mex 之异或 = t（末位 mex 恒为 n，k = t ^ n）
    if (t <= n - 1) {
        // mex 序列：0,...,0, t, n（t=0 时为 0,...,0, n），异或 = t ^ n = k
        std::cout << "YES" << '\n';
        for (int i = 1; i <= n - 1; i++) {
            if (i != t) {
                std::cout << i << ' ';
            }
        }
        if (n > 1 && t != 0) { // t=0 时末尾的 t 本身就是 0，不能再输出中间的 0
            std::cout << 0 << ' ';
        }
        std::cout << t << '\n';
    } else {
        if (bitLength(t) > bitLength(n - 1)) {
            std::cout << "NO" << '\n';
        } else {
            // t 与 n-1 最高位相同，v = t ^ (n-1) 满足 0 < v < n-1
            // mex 序列：0,...,0, v, n-1, n，异或 = v ^ (n-1) ^ n = t ^ n = k
            std::cout << "YES" << '\n';
            int v = t ^ (n - 1);
            for (int i = 1; i < n - 1; i++) {
                if (i != v) {
                    std::cout << i << ' ';
                }
            }
            if (n > 2) {
                std::cout << 0 << ' ';
            }
            std::cout << v << ' ' << n - 1 << '\n';
        }
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
