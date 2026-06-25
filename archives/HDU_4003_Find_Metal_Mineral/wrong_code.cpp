#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(1e4) + 5;

int n, m, root;
int H[N];
struct EdgeNode {
    int v, w, n;
} E[N * 2];
int idx;

void init() {
    idx = 0;
    memset(H, 0, sizeof(H));
}

void add(int a, int b, int w) {
    E[++idx] = {b, w, H[a]}, H[a] = idx;
}

int f[N][15];

void dfs(int u, int fa) {
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            dfs(v, u);
            for (int j = m; j >= 1; j--) {
                for (int k = 1; k <= j; k++) {
                    // BUG: f[u][j] 没有先加上 v 子树未分配机器人时的基础费用 2*w
                    f[u][j] = std::min(f[u][j], f[u][j - k] + f[v][k] + k * w);
                }
            }
            f[u][0] += f[v][0] + 2 * w; // 只更新了 f[u][0]，漏了 f[u][j≥1]
        }
    }
}

void solve() {
    init();
    memset(f, 0, sizeof(f));
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        add(a, b, w), add(b, a, w);
    }
    dfs(root, -1);
    std::cout << f[root][m] << '\n';
}

int main() {
    while (std::cin >> n >> root >> m) {
        solve();
    }
    return 0;
}
