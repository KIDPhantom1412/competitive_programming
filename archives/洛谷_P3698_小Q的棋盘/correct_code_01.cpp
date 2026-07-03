#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 110;

int n, m;
bool G[N][N];
int maxDepth;

// DFS 求从根出发的最长路径上的节点数
void dfs(int u, int fa, int depth) {
    maxDepth = std::max(maxDepth, depth);
    for (int v = 0; v < n; v++) {
        if (G[u][v] && v != fa) {
            dfs(v, u, depth + 1);
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
        G[a][b] = G[b][a] = true;
    }
    dfs(0, -1, 1);                          // depth 从 1 开始，表示路径上的节点数
    if (m <= maxDepth - 1) {                // 步数不够走完最长链
        std::cout << m + 1 << '\n';
    } else {                                // 走完最长链 + 剩余步数探索支路
        // 关键：用 min(n, ...) 限制答案不超过总节点数
        std::cout << std::min(n, maxDepth + (m - maxDepth + 1) / 2) << '\n';
    }
    return 0;
}
