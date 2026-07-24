#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 160;

int n, m;
int H[N];
struct EdgeNode {
    int v, n;
} E[N * 2];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int size[N];
int f[N][N];

// f[u][j]：在 u 的子树（相对于根 1）中，删除最少边数，使得存在一个
// 大小为 j 且包含 u 的连通块。
void dfs(int u, int fa) {
    size[u] = 1;
    std::fill(f[u], f[u] + m + 1, N);
    f[u][1] = 0; // 只保留 u 自己，不删边

    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v == fa) continue;

        dfs(v, u);
        size[u] += size[v];

        // j 从大到小枚举，保证 f[u][j - k] 仍是处理 v 之前的旧值
        for (int j = std::min(size[u], m); j >= 1; j--) {
            f[u][j] += 1; // 方案 1：切断 u-v 这条边

            // 方案 2：保留 u-v，从 v 的子树中合并 k 个节点
            for (int k = std::max(0, j - (size[u] - size[v]));
                 k <= std::min({size[v], m, j}); k++) {
                f[u][j] = std::min(f[u][j], f[v][k] + f[u][j - k]);
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        add(a, b), add(b, a);
    }

    dfs(1, -1);

    // 最优孤立子树可能不以 1 为根，非根节点需额外切断到父节点的边
    int res = N;
    for (int i = 1; i <= n; i++) {
        res = std::min(res, f[i][m] + (i == 1 ? 0 : 1));
    }
    std::cout << res << '\n';

    return 0;
}
