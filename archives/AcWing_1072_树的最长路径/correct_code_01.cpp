#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(1e4) + 5;

int n;
int H[N];                           // 邻接表头指针
struct EdgeNode {
    int v, w, n;                    // 终点、边权、下一条边
} E[N * 2];
int idx;

void add(int a, int b, int w) {
    E[++idx] = {b, w, H[a]}, H[a] = idx;
}

int f[N][2];                        // f[u][0]: u 向下最长链；f[u][1]: 以 u 为最高点的最长路径
int res;

void dfs(int u, int fa) {
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            dfs(v, u);
            // 尝试将之前的最长向下链与 v 子树的最长向下链在 u 处拼接
            f[u][1] = std::max(f[u][1], f[u][0] + f[v][0] + w);
            // 更新 u 向下的最长链
            f[u][0] = std::max(f[u][0], f[v][0] + w);
        }
    }
    // 答案可能是单链、经过 u 的完整路径或单个节点（0）
    res = std::max({res, f[u][0], f[u][1]});
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        add(a, b, w), add(b, a, w); // 无向边
    }

    dfs(1, -1);

    std::cout << res << '\n';

    return 0;
}
