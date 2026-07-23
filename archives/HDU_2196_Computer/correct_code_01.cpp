#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(1e4) + 5;

int n;
int H[N];                        // 链式前向星头节点
struct EdgeNode {
    int v, w, n;                 // 终点、边权、下一条边
} E[N * 2];
int idx;

void add(int a, int b, int w) {
    E[++idx] = {b, w, H[a]}, H[a] = idx;
}

void clear() {
    idx = 0;
    ::memset(H, 0, sizeof(H));
}

int dn1[N], dn2[N], dc[N];       // 向下最长、次长距离，最长来源子节点

// 第一遍 DFS：计算每个节点向下的最长/次长距离
void dfs1(int u, int fa) {
    dn1[u] = dn2[u] = 0;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            dfs1(v, u);
            int d = dn1[v] + w;
            if (d > dn1[u]) {
                dn2[u] = dn1[u];
                dn1[u] = d;
                dc[u] = v;
            } else if (d > dn2[u]) {
                dn2[u] = d;
            }
        }
    }
}

int up[N];                       // 每个节点向上的最长距离

// 第二遍 DFS：换根计算向上的最长距离
void dfs2(int u, int fa) {
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            up[v] = up[u] + w;
            if (dc[u] == v) {
                // v 是 u 向下最长路径的来源，不能重复用 dn1[u]
                up[v] = std::max(up[v], dn2[u] + w);
            } else {
                up[v] = std::max(up[v], dn1[u] + w);
            }
            dfs2(v, u);
        }
    }
}

void solve() {
    clear();                     // 坑点：多组数据必须清空图
    for (int i = 2; i <= n; i++) {
        int j, w;
        std::cin >> j >> w;
        add(i, j, w), add(j, i, w);
    }

    dfs1(1, -1);
    dfs2(1, -1);

    for (int i = 1; i <= n; i++) {
        std::cout << std::max(up[i], dn1[i]) << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n) {      // 坑点：多组数据读至 EOF
        solve();
    }

    return 0;
}
