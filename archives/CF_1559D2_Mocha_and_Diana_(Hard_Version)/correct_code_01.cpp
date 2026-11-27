// CF 1559D2 - Mocha and Diana (Hard Version)
// 网格模型：行 = Mocha 连通块，列 = Diana 连通块，格子 (i, j) = 同属两块的点。
// 一次加边 = 取不同行不同列的两个非空格子，连接其代表点并合并两行两列；
// 行/列集合小合大维护，共做 min(c1, c2) - 1 次，O(n log^2 n)。
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

const int N = int(1e5) + 5;

int P1[N]; // Mocha 森林（行）的并查集
int P2[N]; // Diana 森林（列）的并查集

int find(int P[], int x) {
    if (x != P[x]) {
        P[x] = find(P, P[x]);
    }
    return P[x];
}

void solve() {
    int n, m1, m2;
    std::cin >> n >> m1 >> m2;
    for (int i = 1; i <= n; i++) { // DSU 必须初始化，全局数组默认全 0
        P1[i] = i;
        P2[i] = i;
    }
    for (int i = 0; i < m1; i++) {
        int a, b;
        std::cin >> a >> b;
        P1[find(P1, a)] = P1[find(P1, b)];
    }
    for (int i = 0; i < m2; i++) {
        int a, b;
        std::cin >> a >> b;
        P2[find(P2, a)] = P2[find(P2, b)];
    }
    if (m1 < m2) {
        std::swap(P1, P2); // WLOG assume there are fewer rows than columns（块数 = n - 边数）
    }

    std::map<int, std::set<int>> A, B;
    std::map<int, std::map<int, int>> overlap;
    for (int i = 1; i <= n; i++) {
        overlap[find(P1, i)][find(P2, i)] = i; // 只保留一个代表性节点即可，多了也没用
        A[find(P1, i)].insert(find(P2, i));
        B[find(P2, i)].insert(find(P1, i));
    }

    std::set<std::pair<int, int>> rows; // (-集合大小, 行)，最小元素即最大行
    for (int i = 1; i <= n; i++) {
        if (i == P1[i]) {
            rows.insert({-int(A[i].size()), i});
        }
    }

    auto mergeForest = [&](int a1, int a2, int b1, int b2) -> void {
        // 小合大合并行 a2 -> a1
        for (int b : A[a2]) {
            A[a1].insert(b);
            overlap[a1][b] = overlap[a2][b];
            B[b].erase(a2);
            B[b].insert(a1);
        }
        overlap.erase(a2);
        A.erase(a2);

        // 小合大合并列 b2 -> b1；行 a 的集合大小会变，须同步维护 rows
        for (int a : B[b2]) {
            rows.erase({-int(A[a].size()), a});
            B[b1].insert(a);
            overlap[a][b1] = overlap[a][b2];
            overlap[a].erase(b2);
            A[a].erase(b2);
            A[a].insert(b1);
            rows.insert({-int(A[a].size()), a});
        }
        B.erase(b2);
    };

    std::vector<std::pair<int, int>> res;
    while (rows.size() > 1) {
        int a1 = rows.begin()->second;
        rows.erase(rows.begin());
        int a2 = rows.begin()->second;
        rows.erase(rows.begin());
        if (A[a1].size() < A[a2].size()) {
            std::swap(a1, a2); // 保证 |A[a1]| >= |A[a2]|，小合大且 *++it 安全
        }
        int b1 = *A[a1].begin();
        int b2 = *A[a2].begin();
        if (b1 == b2) {
            auto it = A[a1].begin();
            b1 = *++it; // 相撞时 |A[a1]| >= 2（全单点行两两互不相交，不会相撞）
        }
        res.push_back({overlap[a1][b1], overlap[a2][b2]}); // 不同行不同列的两个格子
        if (B[b1].size() < B[b2].size()) {
            std::swap(b1, b2); // 列合并同样小合大
        }
        mergeForest(a1, a2, b1, b2);
        rows.insert({-int(A[a1].size()), a1});
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
