#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> G(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    int root, ts = 0;
    std::vector<int> low(n + 1), dfn(n + 1);
    std::set<int> cut; // 用 set 天然去重并按编号升序
    auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
        int child = 0;
        dfn[u] = low[u] = ++ts;
        for (int v : G[u]) {
            if (v == fa) {
                continue; // 无向图不能沿父边回去
            }

            if (!dfn[v]) {
                child++;
                dfs(v, u);
                low[u] = std::min(low[u], low[v]);

                // 非根节点：某个子树无法绕过 u 回到 u 的祖先
                if (u != root && low[v] >= dfn[u]) {
                    cut.insert(u);
                }
            } else {
                // 返祖边，用 dfn 更新（不能用 low）
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        // 根节点：至少两棵子树才会被割出多个连通块
        if (u == root && child >= 2) {
            cut.insert(u);
        }
    };

    // 图不一定连通，每个未访问点都要作为新的一棵搜索树的根启动
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            root = i;
            dfs(i, -1);
        }
    }

    std::cout << cut.size() << '\n';
    for (int u : cut) {
        std::cout << u << ' ';
    }
    std::cout << '\n';
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
