#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 110, INF = int(1e9) + 5;

int n, m;
int H[N];
struct EdgeNode {
    int v, w, n;
} E[N * 2];  // 双向边，要开两倍

void add(int a, int b, int w) {
    static int idx = 1;
    E[++idx] = {b, w, H[a]}, H[a] = idx;
}

int size[N];
int f[N][N];

// 边数树形背包：f[u][j] 表示在 u 的子树里保留 j 条边（不含父边）的最大权值
void dfs(int u, int fa) {
    size[u] = 1;
    f[u][0] = 0;
    std::fill(f[u] + 1, f[u] + N, -INF);
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            dfs(v, u);
            size[u] += size[v];
            for (int j = std::min(size[u], m); j >= 0; j--) {
                for (int k = 0; k <= std::min(size[v], j - 1); k++) {
                    f[u][j] = std::max(f[u][j], f[u][j - k - 1] + f[v][k] + w);
                }
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        add(a, b, w), add(b, a, w);
    }

    dfs(1, -1);

    std::cout << f[1][m] << '\n';

    return 0;
}
