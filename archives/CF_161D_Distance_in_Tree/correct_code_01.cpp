#include <cstdint>
#include <iostream>
#include <vector>

void solve() {
    int n, K;
    std::cin >> n >> K;
    std::vector<std::vector<int>> G(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    // f[u][d]：u 的子树中，到 u 距离恰好为 d 的点数
    std::vector<std::vector<int>> f(n + 1, std::vector<int>(K + 1));
    int64_t res = 0;
    auto dfs = [&](this auto&& dfs, int u, int fa) -> void {
        f[u][0] = 1;
        for (int v : G[u]) {
            if (v != fa) {
                dfs(v, u);
                // 先与已经合并进 u 的部分配对。此时点对的 LCA 是 u，且每对只计一次
                for (int i = 1; i <= K; i++) {
                    res += f[u][K - i] * f[v][i - 1];
                }
                // 再把 v 子树并入 u，到 u 的距离比到 v 的距离多 1
                for (int i = 0; i < K; i++) {
                    f[u][i + 1] += f[v][i];
                }
            }
        }
    };
    dfs(1, -1);
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
