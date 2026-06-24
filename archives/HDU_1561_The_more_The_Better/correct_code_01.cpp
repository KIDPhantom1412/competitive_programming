#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 210;

int n, m;
int W[N];
int H[N];
struct EdgeNode {
    int v, n;
} E[N];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int f[N][N];

void dfs(int u) {
    // 初始化：本题中 b >= 0，因此把所有 f[u][i] 设为 W[u] 是安全的下界
    for (int i = 1; i <= m + 1; i++) {
        f[u][i] = W[u];
    }
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        dfs(v);
        // 0/1 背包合并子树 v
        for (int j = m + 1; j >= 1; j--) {
            for (int k = 1; k <= j - 1; k++) {
                f[u][j] = std::max(f[u][j], f[u][j - k] + f[v][k]);
            }
        }
    }
}

void solve() {
    idx = 0;
    memset(H, 0, sizeof(H));
    memset(f, 0, sizeof(f));
    for (int i = 1; i <= n; i++) {
        int a, b;
        std::cin >> a >> b;
        add(a, i);   // a 是 i 的父节点（必须先攻克 a）
        W[i] = b;
    }
    dfs(0);
    std::cout << f[0][m + 1] << '\n';
}

int main() {
    while (std::cin >> n >> m, n || m) {
        solve();
    }
    return 0;
}
