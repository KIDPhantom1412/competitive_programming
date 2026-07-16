#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(1e4) + 5;

int n;
int H[N];                           // 邻接表头指针
struct EdgeNode {
    int v, w, n;                    // 终点、边权、下一条边
} E[N * 2];

void add(int a, int b, int w) {
    static int idx;
    E[++idx] = {b, w, H[a]}, H[a] = idx;
}

int res;

int dfs(int u, int fa) {
    int d1 = 0, d2 = 0;             // 最长、次长向下链
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v, w = E[i].w;
        if (v != fa) {
            int d = dfs(v, u) + w;
            if (d > d1) {
                d2 = d1;
                d1 = d;
            } else if (d > d2) {
                d2 = d;
            }
        }
    }
    // 经过 u 的最长路径 = 最长向下链 + 次长向下链
    res = std::max(res, d1 + d2);
    return d1;                      // 返回向下的最长链
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
