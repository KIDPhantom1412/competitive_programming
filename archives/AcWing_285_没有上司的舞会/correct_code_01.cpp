#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 6010;

int n;
int W[N];          // 每个职员的快乐指数
int H[N];          // 链式前向星表头
struct EdgeNode {
    int v, n;
} E[N * 2];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int f[N][2];       // f[u][0]: 不选 u 时的最大快乐指数
                   // f[u][1]: 选 u 时的最大快乐指数

void dfs(int u, int fa) {
    f[u][0] = 0;
    f[u][1] = W[u];
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs(v, u);
            // 父节点不选，子节点可选可不选，取最大值
            f[u][0] += std::max(f[v][0], f[v][1]);
            // 父节点选，子节点一定不选
            f[u][1] += f[v][0];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> W[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        add(a, b), add(b, a);  // 按无向边建树，任意节点为根均可
    }

    dfs(1, -1);

    std::cout << std::max(f[1][0], f[1][1]) << '\n';

    return 0;
}
