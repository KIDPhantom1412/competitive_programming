#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(1e4) + 5, INF = int(1e9) + 5;

int n;
int H[N];  // 邻接表头指针
struct EdgeNode {
    int v, w, n;  // 终点、边权、下一条边
} E[N * 2];

// 链式前向星加边
void add(int a, int b, int w) {
    static int idx = 1;
    E[++idx] = {b, w, H[a]}, H[a] = idx;
}

// d1[u]: 从 u 向下的最长路径
// d2[u]: 从 u 向下的次长路径
// dc[u]: d1[u] 经过的子节点
int d1[N], d2[N], dc[N];

// up[u]: 从 u 向上（经过父节点）的最长路径
int up[N];

// 后序 DFS，求 d1 / d2 / dc
int dfs1(int u, int fa) {
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            int d = dfs1(v, u) + w;
            if (d > d1[u]) {
                d2[u] = d1[u];
                d1[u] = d;
                dc[u] = v;
            } else if (d > d2[u]) {
                d2[u] = d;
            }
        }
    }
    return d1[u];
}

// 先序 DFS，求 up
void dfs2(int u, int fa) {
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            // 从 v 向上走：要么继续沿 u 的向上路径，
            // 要么从 u 走一条不经过 v 的向下路径
            if (dc[u] == v) {
                up[v] = std::max(up[u] + w, d2[u] + w);
            } else {
                up[v] = std::max(up[u] + w, d1[u] + w);
            }
            dfs2(v, u);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b, w;
        std::cin >> a >> b >> w;
        add(a, b, w), add(b, a, w);
    }

    dfs1(1, -1);
    dfs2(1, -1);

    // 偏心距 = max(向下最远距离, 向上最远距离)
    int res = INF;
    for (int i = 1; i <= n; i++) {
        res = std::min(res, std::max(d1[i], up[i]));
    }
    std::cout << res << '\n';

    return 0;
}
