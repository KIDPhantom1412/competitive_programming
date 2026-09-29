#include <iostream>

void solve() {
    int n;
    std::cin >> n;
    if (n < 4) {
        std::cout << -1 << '\n';
        return;
    }

    // 奇数倒序，相邻差为 2；最后一个数是 1。
    for (int i = (n % 2) ? n : n - 1; i >= 1; i -= 2) {
        std::cout << i << ' ';
    }

    // 1 -> 4 -> 2 的相邻差分别为 3、2。
    std::cout << "4 2 ";

    // 若存在 6，则 2 -> 6 的差为 4；之后相邻差均为 2。
    for (int i = 6; i <= n; i += 2) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
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
