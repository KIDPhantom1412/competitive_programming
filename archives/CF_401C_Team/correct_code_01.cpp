#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    // n 个 0 隔出 n+1 个空位，每个空位至多 2 个 1。
    // m 个 1 隔出 m+1 个空位，每个空位至多 1 个 0。
    if (m > 2 * (n + 1) || n > m + 1) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::string res;
    while (n > 0 || m > 0) {
        if (n == 0) {
            res += std::string(m, '1');
            m = 0;
        } else if (m == 0) {
            res += std::string(n, '0');
            n = 0;
        } else if (n > m) {
            // 0 比 1 多一个，先放 0，避免最后接出 "00"。
            res += "01";
            n--;
            m--;
        } else if (m <= n * 2) {
            res += "10";
            n--;
            m--;
        } else {
            res += "110";
            n--;
            m -= 2;
        }
    }

    std::cout << res << '\n';
    return 0;
}
