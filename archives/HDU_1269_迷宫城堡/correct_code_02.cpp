#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

int n, m;
std::vector<std::vector<int>> G;
int ts, cnt;
std::vector<int> low, dfn, scc;
std::stack<int> stk;

void dfs(int u) {
    low[u] = dfn[u] = ++ts;
    stk.push(u); // 当前点入栈，弹分量时才能取到
    for (int v : G[u]) {
        if (dfn[v] == 0) {
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        } else if (scc[v] == 0) {
            // scc 仍为 0 表示 v 还在栈中，用返祖边或横叉边更新 low
            low[u] = std::min(low[u], dfn[v]);
        }
    }

    if (low[u] == dfn[u]) {
        // u 是当前强连通分量的根，弹栈直到 u
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
}

void solve() {
    // 多组数据必须整表重建，resize 不会清掉旧边和旧标记
    G.assign(n + 1, {});
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].push_back(b);
    }

    ts = cnt = 0;
    low.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    scc.assign(n + 1, 0);
    stk = std::stack<int>{};
    for (int i = 1; i <= n; i++) {
        if (dfn[i] == 0) {
            dfs(i);
        }
    }

    std::cout << (cnt == 1 ? "Yes" : "No") << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m, n || m) {
        solve();
    }

    return 0;
}
