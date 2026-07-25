#include <algorithm>
#include <iostream>

const int N = 110, INF = int(1e9);

int n, m;
int V[N], W[N];
int H[N];
struct EdgeNode {
    int v, n;
} E[N * 2];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int f[N][N];

void dfs(int u, int fa) {
    for (int i = 0; i <= m; i++) {
        f[u][i] = i < V[u] ? -INF : W[u];
    }
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs(v, u);
            // k 必须从 1 开始：进入子树至少需要 1 个士兵
            for (int j = m; j >= 1; j--) {
                for (int k = 1; k <= j; k++) {
                    f[u][j] = std::max(f[u][j], f[v][k] + f[u][j - k]);
                }
            }
        }
    }
}

void solve() {
    idx = 0;
    std::fill_n(H, N, 0);
    for (int i = 1; i <= n; i++) {
        std::cin >> V[i] >> W[i];
        V[i] = (V[i] + 19) / 20;
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        add(a, b), add(b, a);
    }
    // 没有士兵时，即使入口房间没怪，也拿不到脑子
    if (m == 0) {
        std::cout << 0 << '\n';
        return;
    }
    dfs(1, -1);
    std::cout << std::max(0, f[1][m]) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m, !(n == -1 && m == -1)) {
        solve();
    }

    return 0;
}
