#include <iostream>

void solve() {
    int k, x, a;
    std::cin >> k >> x >> a;
    // z：本轮已经连续输掉的总额。最坏是连败 x 次，第 x+1 次被迫获胜。
    int z = 0;
    for (int i = 1; i <= x + 1; i++) {
        // 若这次获胜，净赚 y*(k-1)，必须至少比已输的 z 多 1。
        int y = z / (k - 1) + 1;
        if (a - y < 0) {
            std::cout << "NO" << '\n';
            return;
        }
        a -= y;
        z += y;
    }
    std::cout << "YES" << '\n';
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
