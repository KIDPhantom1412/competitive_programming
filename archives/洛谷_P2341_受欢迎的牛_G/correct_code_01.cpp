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
    int cnt = 0;
    std::vector<int> scc(n + 1); // scc[i]：点 i 所属 SCC 编号，0 表示尚未出栈
    auto dfs = [&](this auto&& dfs, int u) -> void {
        dfn[u] = low[u] = ++ts;
        stk.push(u);
        for (int v : G[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (!scc[v]) {
                // 只有仍在栈中的点才是回边；
                // 已出栈的点属于已完成的 SCC，不能再用 dfn[v] 拉低 low[u]
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) { // u 是当前 SCC 的根
            cnt++;
            while (true) {
                int x = stk.top();
                scc[x] = cnt;
                stk.pop();
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

    // 缩点后统计每个 SCC 的出度（重边不影响"是否为 0"的判断）
    std::vector<int> out(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j : G[i]) {
            if (scc[i] != scc[j]) {
                out[scc[i]]++;
            }
        }
    }

    // 出度为 0 的 SCC 必须唯一，它才是所有点都能到达的汇点
    int zero = 0, idx = 0;
    for (int i = 1; i <= cnt; i++) {
        if (out[i] == 0) {
            zero++;
            if (zero >= 2) {
                std::cout << 0 << '\n';
                return;
            }
            idx = i;
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        res += scc[i] == idx;
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
