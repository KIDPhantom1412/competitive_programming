#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> G(n + 1);
    for (int i = 1; i <= n; i++) {
        int j;
        while (std::cin >> j, j) {
            G[i].push_back(j);
        }
    }

    // ---------- Tarjan 求 SCC ----------
    int ts = 0;
    std::vector<int> dfn(n + 1), low(n + 1);
    std::stack<int> stk;
    int cnt = 0;
    std::vector<int> scc(n + 1);
    auto dfs = [&](this auto&& dfs, int u) -> void {
        dfn[u] = low[u] = ++ts;
        stk.push(u);
        for (int v : G[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (!scc[v]) {
                // v 在栈中（未归属任何 SCC）才是回边/横叉边，取 dfn[v]
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        // 找到 SCC 根，弹出整个 SCC
        if (dfn[u] == low[u]) {
            cnt++;
            while (true) {
                int v = stk.top();
                stk.pop();
                scc[v] = cnt;
                if (u == v) {
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

    // ---------- 缩点统计各 SCC 入度/出度（同一 SCC 内部的边不计）----------
    std::vector<int> out(cnt + 1), ind(cnt + 1);
    for (int i = 1; i <= n; i++) {
        for (int j : G[i]) {
            if (scc[i] != scc[j]) {
                out[scc[i]]++;
                ind[scc[j]]++;
            }
        }
    }

    int outZero = 0, indZero = 0;
    for (int i = 1; i <= cnt; i++) {
        outZero += out[i] == 0;
        indZero += ind[i] == 0;
    }

    // 问题 1：入度为 0 的 SCC 个数
    std::cout << indZero << '\n';
    // 问题 2：max(入度0个数, 出度0个数)；整图强连通（cnt == 1）时特判为 0
    if (cnt == 1) {
        std::cout << 0 << '\n';
    } else {
        std::cout << std::max(indZero, outZero) << '\n';
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
