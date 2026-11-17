#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> A1(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A1[i];
    }
    std::vector<std::vector<int>> G1(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        G1[a].push_back(b);
    }

    // Tarjan
    int ts = 0;
    std::vector<int> low(n + 1), dfn(n + 1);
    std::vector<bool> st(n + 1);
    std::stack<int> stk;
    int cnt = 0;
    std::vector<int> scc(n + 1);

    auto dfs = [&](this auto&& dfs, int u) -> void {
        low[u] = dfn[u] = ++ts;
        stk.push(u);
        st[u] = true; // 只有还在栈里的点才能更新 low
        for (int v : G1[u]) {
            if (dfn[v] == 0) {
                dfs(v);
                low[u] = std::min(low[u], low[v]);
            } else if (st[v]) {
                // v 仍在栈中：返祖边，或指向栈中点的横叉边
                low[u] = std::min(low[u], dfn[v]);
            }
        }

        if (low[u] == dfn[u]) {
            // u 是当前强连通分量的根，弹栈直到 u
            cnt++;
            while (true) {
                int v = stk.top();
                stk.pop();
                st[v] = false;
                scc[v] = cnt;
                if (u == v) {
                    break;
                }
            }
        }
    };

    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }

    // 拓扑排序上的动态规划
    std::vector<std::vector<int>> G2(cnt + 1);
    std::vector<int> A2(cnt + 1);
    std::vector<int> inDegree(cnt + 1);
    for (int u = 1; u <= n; u++) {
        A2[scc[u]] += A1[u]; // 点权非负，经过分量就把里面的点权全拿上
        for (int v : G1[u]) {
            if (scc[u] != scc[v]) {
                G2[scc[u]].push_back(scc[v]);
                inDegree[scc[v]]++;
            }
        }
    }

    std::queue<int> Q;
    for (int i = 1; i <= cnt; i++) {
        if (inDegree[i] == 0) {
            Q.push(i);
        }
    }

    std::vector<int> f = A2;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        for (int v : G2[u]) {
            f[v] = std::max(f[v], f[u] + A2[v]); // v 的点权只加这一次
            if (--inDegree[v] == 0) {
                Q.push(v);
            }
        }
    }

    std::cout << *std::max_element(f.begin(), f.end()) << '\n';
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
