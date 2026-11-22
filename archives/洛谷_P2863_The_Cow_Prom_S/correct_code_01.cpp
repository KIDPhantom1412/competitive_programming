#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> G(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].push_back(b);
    }

    int ts = 0;
    std::vector<int> dfn(n + 1), low(n + 1);
    std::stack<int> stk;
    std::vector<bool> inStk(n + 1);
    std::vector<std::vector<int>> scc;
    auto dfs = [&](this auto&& dfs, int u) -> void {
        dfn[u] = low[u] = ++ts;
        stk.push(u);
        inStk[u] = true;
        for (int v : G[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (inStk[v]) {
                // v 还在栈中：回边或指向当前 SCC 的横叉边，用 dfn[v] 更新 low
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        // u 是所在 SCC 的根，弹出整个 SCC
        if (low[u] == dfn[u]) {
            scc.push_back({});
            while (true) {
                int x = stk.top();
                stk.pop();
                inStk[x] = false;
                scc.back().push_back(x);
                if (x == u) {
                    break;
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            dfs(i);
        }
    }

    // 统计点数大于 1 的强连通分量个数
    int res = 0;
    for (auto& s : scc) {
        res += s.size() > 1;
    }
    std::cout << res << '\n';
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
