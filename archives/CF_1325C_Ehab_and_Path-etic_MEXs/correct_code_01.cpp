#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    // edge[u] 存 {邻点, 该边的输入下标}
    std::vector<std::vector<std::pair<int, int>>> edge(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        edge[a].push_back({b, i});
        edge[b].push_back({a, i});
    }
    // res[i] = 第 i 条边（输入顺序）的标签，-1 表示未赋值
    std::vector<int> res(n - 1, -1);
    int idx = 0;
    // 找到任意一个度数 >= 3 的点，先把最小的一批标签分给它的所有邻边：
    // 任何路径经过该点最多用两条邻边，取不到全部 {0, 1, 2}，故 MEX <= 2
    for (int u = 1; u <= n; u++) {
        if (edge[u].size() >= 3) {
            for (auto [v, i] : edge[u]) {
                res[i] = idx++;
            }
            break;
        }
    }
    // 剩下的边任意递增编号（树是链时这里会把全部边按输入顺序编号）
    for (int i = 0; i < n - 1; i++) {
        if (res[i] == -1) {
            res[i] = idx++;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        std::cout << res[i] << '\n';
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
