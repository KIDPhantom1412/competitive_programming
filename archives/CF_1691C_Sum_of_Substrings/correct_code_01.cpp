#include <iostream>
#include <string>
#include <utility>

void solve() {
    int n, K;
    std::cin >> n >> K;
    std::string s;
    std::cin >> s;

    // f = 11 * (1 的个数) - 10 * s[n - 1] - s[0]。
    // 开头的 1 只做十位，贡献 10；末尾的 1 只做个位，贡献 1；中间的 1 贡献 11。
    int res = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            if (i == 0) {
                res += 10;
            } else if (i < n - 1) {
                res += 11;
            } else {
                res += 1;
            }
        }
    }
    int lastOne = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '1') {
            lastOne = i;
            break;
        }
    }
    // 先把最右边的 1 换到末尾。中间位置减少 10；唯一的 1 原来在开头时只减少 9。
    if (lastOne >= 0 && lastOne < n - 1 && K >= n - 1 - lastOne) {
        K -= n - 1 - lastOne;
        if (lastOne == 0) {
            res -= 9;
        } else {
            res -= 10;
        }
        std::swap(s[lastOne], s.back());
    }
    int firstOne = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            firstOne = i;
            break;
        }
    }
    // 再把最左边的 1 换到开头，减少 1。它已经在末尾时不动，
    if (firstOne > 0 && firstOne != n - 1 && K >= firstOne) {
        K -= firstOne;
        res -= 1;
        std::swap(s[firstOne], s.front());
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
