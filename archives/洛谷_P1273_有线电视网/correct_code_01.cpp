#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 3010, INF = int(1e9);

int n, m;
int W[N * 2];
int H[N * 2];
struct EdgeNode {
    int v, n;
} E[N * 2];

void add(int a, int b) {
    static int idx;
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int pos[N], cnt;
int size[N];
int f[N][N];

void dfs(int u) {
    size[u] = 1;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        dfs(v);
        size[u] += size[v];
    }
    pos[++cnt] = u;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n - m; i++) {
        int t;
        std::cin >> t;
        while (t--) {
            int j, w;
            std::cin >> j >> w;
            add(i, j);
            W[j] = -w; // 边费用计入子结点
        }
    }
    for (int i = n - m + 1; i <= n; i++) {
        int w;
        std::cin >> w;
        W[i] += w; // 叶子：收益 = 愿付金额 - 边费用
    }

    dfs(1);
    for (int i = 0; i <= cnt; i++) {
        std::fill(f[i] + 1, f[i] + m + 1, -INF); // 注意覆盖下标 m
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= m; j++) {
            if (pos[i] <= n - m) { // 内部结点：跳过整棵子树 或 保留该点
                f[i][j] = std::max(f[i - 1][j] + W[pos[i]], f[i - size[pos[i]]][j]);
            } else { // 叶子：选（消耗 1 个用户名额）或不选
                f[i][j] = std::max(f[i - 1][j - 1] + W[pos[i]], f[i - 1][j]);
            }
        }
    }

    int res = 0;
    for (int j = m; j >= 0; j--) {
        if (f[cnt][j] >= 0) { // 根在后序最后一个位置
            res = j;
            break;
        }
    }
    std::cout << res << '\n';

    return 0;
}
