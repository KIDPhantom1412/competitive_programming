#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

const int MOD = int(1e9) + 7;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> cost(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> cost[i];
    }
    int m;
    std::cin >> m;
    std::vector<std::vector<int>> G(n + 1), rG(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].push_back(b);
        rG[b].push_back(a);
    }

    // Kosaraju 第一遍：原图 DFS，按结束时间记录顺序。
    std::vector<bool> st(n + 1);
    std::vector<int> order;
    auto dfs1 = [&](this auto&& dfs1, int u) -> void {
        st[u] = true;
        for (int v : G[u]) {
            if (!st[v]) {
                dfs1(v);
            }
        }
        order.push_back(u);
    };
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            dfs1(i);
        }
    }

    // 第二遍：按结束顺序的逆序，在反图上走出每个强连通分量。
    std::vector<std::vector<int>> scc;
    auto dfs2 = [&](this auto&& dfs2, int u) -> void {
        scc.back().push_back(u);
        st[u] = true;
        for (int v : rG[u]) {
            if (!st[v]) {
                dfs2(v);
            }
        }
    };
    std::fill(st.begin(), st.end(), false);
    for (int i = (int) order.size() - 1; i >= 0; i--) {
        if (!st[order[i]]) {
            scc.push_back({});
            dfs2(order[i]);
        }
    }

    // 每个分量恰好建一个站：费用取最小值，方案数是取到该最小值的点数。
    int64_t res1 = 0, res2 = 1;
    for (auto& S : scc) {
        int mn = std::numeric_limits<int>::max();
        int cnt = 0;
        for (int v : S) {
            if (cost[v] < mn) {
                cnt = 1;
                mn = cost[v];
            } else if (cost[v] == mn) {
                cnt++;
            }
        }
        res1 += mn;
        res2 = res2 * cnt % MOD;
    }
    std::cout << res1 << ' ' << res2 << '\n';
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
