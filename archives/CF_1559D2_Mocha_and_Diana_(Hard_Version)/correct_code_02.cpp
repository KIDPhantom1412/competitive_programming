// CF 1559D2 - Mocha and Diana (Hard Version)
// 解法：先尽量把点连到 1（阶段1），剩余连通块交叉配对（阶段2）。
// 阶段1 结束后每个点必属于「森林1含1的块」或「森林2含1的块」，
// 于是森林1中不含 1 的块内点在森林2中全落在含 1 的块（反之亦然），
// 两边各取代表点任意配对连边都合法，O(n α(n))。
#include <iostream>
#include <utility>
#include <vector>

const int N = int(1e5) + 5;

int P1[N]; // Mocha 森林的并查集
int P2[N]; // Diana 森林的并查集

int find(int P[], int x) {
    if (x != P[x]) {
        P[x] = find(P, P[x]);
    }
    return P[x];
}

void solve() {
    int n, m1, m2;
    std::cin >> n >> m1 >> m2;
    for (int i = 1; i <= n; i++) { // DSU 初始化，全局数组默认全 0
        P1[i] = i;
        P2[i] = i;
    }
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

    // 阶段1：把所有还能与 1 相连的点连到 1（两边都不同连通块才可连）
    for (int i = 2; i <= n; i++) {
        if (find(P1, 1) != find(P1, i) && find(P2, 1) != find(P2, i)) {
            res.push_back({1, i});
            P1[find(P1, i)] = find(P1, 1);
            P2[find(P2, i)] = find(P2, 1);
        }
    }

    // 阶段2：X = 森林1中不含 1 的连通块，Y = 森林2中不含 1 的连通块。
    // X 块内的点在森林2必属于含 1 的块，Y 块内的点在森林1必属于含 1 的块，
    // 所以 X[k] 与 Y[k] 在两边都不同块，任意顺序两两配对必合法。
    int r1 = find(P1, 1), r2 = find(P2, 1);
    std::vector<int> X, Y;
    for (int i = 1; i <= n; i++) {
        if (P1[i] == i && i != r1) { // 用连通块的根作代表点
            X.push_back(i);
        }
        if (P2[i] == i && i != r2) {
            Y.push_back(i);
        }
    }
    for (int k = 0; k < int(X.size()) && k < int(Y.size()); k++) {
        res.push_back({X[k], Y[k]});
        P1[find(P1, X[k])] = find(P1, Y[k]);
        P2[find(P2, X[k])] = find(P2, Y[k]);
    }

    std::cout << res.size() << '\n';
    for (auto [a, b] : res) {
        std::cout << a << ' ' << b << '\n';
    }
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
