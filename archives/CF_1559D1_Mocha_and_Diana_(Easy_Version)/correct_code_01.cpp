#include <iostream>
#include <utility>
#include <vector>

void solve() {
    int n, m1, m2;
    std::cin >> n >> m1 >> m2;
    std::vector<int> P1(n + 1), P2(n + 1);
    for (int i = 1; i <= n; i++) {
        P1[i] = P2[i] = i;
    }
    auto find = [&](this auto&& find, std::vector<int>& P, int x) -> int {
        if (x != P[x]) {
            P[x] = find(P, P[x]);
        }
        return P[x];
    };
    // 分别建立 Mocha（P1）与 Diana（P2）两片森林的并查集
    for (int i = 0; i < m1; i++) {
        int a, b;
        std::cin >> a >> b;
        P1[find(P1, a)] = find(P1, b);
    }
    for (int i = 0; i < m2; i++) {
        int a, b;
        std::cin >> a >> b;
        P2[find(P2, a)] = find(P2, b);
    }
    std::vector<std::pair<int, int>> res;
    // 枚举所有点对，两边都不同连通块则加边并同时合并
    // 只要两边都剩 >=2 个连通块就必存在合法点对，贪心即最优
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            if (find(P1, i) != find(P1, j) && find(P2, i) != find(P2, j)) {
                P1[find(P1, i)] = find(P1, j);
                P2[find(P2, i)] = find(P2, j);
                res.push_back({i, j});
            }
        }
    }
    std::cout << res.size() << '\n';
    for (auto [a, b] : res) {
        std::cout << a << ' ' << b << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();

    return 0;
}
