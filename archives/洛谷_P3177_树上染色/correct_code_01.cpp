#include <algorithm>
#include <cstring>
#include <iostream>

using LL = long long;

const int N = 2010;

int n, m;                 // m 为全局黑点数量（已取 min(k, n-k)）
int H[N];
struct EdgeNode {
    int v, w, n;
} E[N * 2];
int idx;

void add(int a, int b, int w) {
    E[++idx] = {b, w, H[a]}, H[a] = idx;
}

int size[N];              // 子树大小
LL f[N][N];               // f[u][j]：u 子树中染 j 个黑点的最大收益

void dfs(int u, int fa) {
    size[u] = 1;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            dfs(v, u);
            size[u] += size[v];

            // 树形背包：j 从大到小，避免同一子树被重复选取
            for (int j = std::min(size[u], m); j >= 0; j--) {
                // k 为子树 v 中的黑点数，必须同时满足 k <= j 且 k <= size[v]
                for (int k = std::max(0, j - (size[u] - size[v]));
                     k <= std::min(j, size[v]); k++) {
                    // 边 (u,v) 的贡献：
                    // 黑点对数 k*(m-k) + 白点对数 (size[v]-k)*(n-m-(size[v]-k))
                    f[u][j] = std::max(
                        f[u][j],
                        f[u][j - k] + f[v][k] +
                            (k * LL(m - k) +
                             LL(size[v] - k) * (n - m - (size[v] - k))) *
                                w);
                }
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    if (n - m < m) {
        m = n - m;        // 利用颜色对称，只需考虑较少的颜色
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        add(a, b, w), add(b, a, w);
    }

    dfs(1, -1);

    std::cout << f[1][m] << '\n';

    return 0;
}
