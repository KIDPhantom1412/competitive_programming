#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 1510, INF = int(1e9);

int n;
int W[N];
int H[N];
struct EdgeNode {
    int v, n;
} E[N * 2];

void add(int a, int b) {
    static int idx;
    E[++idx] = {b, H[a]}, H[a] = idx;
}

// f[u][0]: u 被父亲覆盖；f[u][1]: u 被孩子覆盖；f[u][2]: u 自己放守卫
int f[N][3];

void dfs(int u, int fa) {
    f[u][1] = INF;
    f[u][2] = W[u];
    // extra: 让所有孩子取最优后，再强制一个孩子放守卫的最小增量
    int extra = INF;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs(v, u);
            int t = std::min(f[v][1], f[v][2]);
            f[u][0] += t; // u 被父亲覆盖，孩子只需被覆盖
            f[u][2] += std::min({f[v][0], f[v][1], f[v][2]}); // u 放守卫，孩子随意
            extra = std::min(extra, f[v][2] - t); // f[v][2] >= t，增量非负
        }
    }
    if (extra != INF) { // 叶子没有孩子，f[u][1] 保持 INF
        f[u][1] = f[u][0] + extra;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        int u, w, t;
        std::cin >> u >> w >> t;
        W[u] = w;
        while (t--) {
            int v;
            std::cin >> v;
            add(u, v), add(v, u);
        }
    }

    dfs(1, -1);

    std::cout << std::min(f[1][1], f[1][2]) << '\n';

    return 0;
}
