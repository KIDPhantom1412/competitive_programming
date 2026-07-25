#include <algorithm>
#include <iostream>

const int N = 110, M = 210, INF = int(1e9);

int n, m;
int W[N];
int H[N];
struct EdgeNode {
    int v, n;
} E[N * 2];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int f[N][M][2];

// f[u][j][0]: 从 u 出发在子树内走 j 步，最终回到 u 的最大苹果数
// f[u][j][1]: 从 u 出发在子树内走 j 步，最终不回到 u 的最大苹果数
void dfs(int u, int fa) {
    // 关键：f[u] 一行有 M * 2 个整数，不能只填 N * 2
    std::fill_n(reinterpret_cast<int*>(f[u]), M * 2, -INF);
    f[u][0][0] = W[u];
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs(v, u);
            for (int j = m; j >= 1; j--) {
                for (int k = 0; k < j; k++) {
                    // 不返回 v，之前所有子树都返回 u
                    f[u][j][1] = std::max(
                        f[u][j][1], f[u][j - k - 1][0] + std::max(f[v][k][0], f[v][k][1]));
                    if (j - k - 2 >= 0) {
                        // 返回 v，但之前已经有子树不返回
                        f[u][j][1] = std::max(f[u][j][1], f[u][j - k - 2][1] + f[v][k][0]);
                        // 返回 v，之前所有子树都返回
                        f[u][j][0] = std::max(f[u][j][0], f[u][j - k - 2][0] + f[v][k][0]);
                    }
                }
            }
        }
    }
}

void solve() {
    idx = 0;
    std::fill_n(H, N, 0);

    for (int i = 1; i <= n; i++) {
        std::cin >> W[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        add(a, b), add(b, a);
    }

    dfs(1, -1);

    int res = 0;
    for (int i = 0; i <= m; i++) {
        res = std::max({res, f[1][i][0], f[1][i][1]});
    }
    std::cout << res << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m) {
        solve();
    }

    return 0;
}
