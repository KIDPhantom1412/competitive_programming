#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

int n;

void solve() {
    std::vector<std::vector<int>> G(n + 1);
    // 按行读入：每行以 u 开头，后续是该点的所有邻接点；单独一行 0 结束本组
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        if (line.empty()) { // 跳过读取 n 时残留的换行
            continue;
        }
        std::stringstream ss(line);
        int u, v;
        ss >> u;
        if (!u) {
            break;
        }

        // 题目只保证每条边"至少"出现在一行里，可能两端各写一次，故允许重复边
        while (ss >> v) {
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }

    int root;
    int ts = 0;
    std::vector<int> low(n + 1), dfn(n + 1);
    std::vector<int> cutVertex(n + 1);
    std::function<void(int, int)> dfs = [&](int u, int fa) -> void {
        dfn[u] = low[u] = ++ts;
        int cnt = 0; // 根节点的子树个数
        for (int v : G[u]) {
            if (v != fa) {
                if (dfn[v] == 0) { // 树边：v 是 u 的儿子
                    cnt++;
                    dfs(v, u);
                    low[u] = std::min(low[u], low[v]);

                    // 割点判据只对树边儿子生效，且必须用 dfn[u] 而非 low[u]
                    if (u != root && low[v] >= dfn[u]) {
                        cutVertex[u] = 1;
                    }
                } else if (dfn[v] < dfn[u]) { // 后向边，用祖先的 dfn 更新 low
                    low[u] = std::min(low[u], dfn[v]);
                }
            }
        }

        // 根节点没有祖先可回退，需要至少两棵子树才是割点
        if (u == root && cnt >= 2) {
            cutVertex[u] = 1;
        }
    };

    // 图可能不连通，对每个连通块分别 DFS（root 需在每次 DFS 前重置）
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            root = i;
            dfs(i, -1);
        }
    }

    // std::accumulate 而非 std::reduce（后者需要 C++17，老评测机可能 CE）
    std::cout << std::accumulate(cutVertex.begin(), cutVertex.end(), 0) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n, n) {
        solve();
    }

    return 0;
}
