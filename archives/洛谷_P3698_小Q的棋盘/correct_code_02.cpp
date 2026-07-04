#include <algorithm>
#include <cstring>
#include <iostream>

const int N = 110;

int n, m;
int H[N];
struct EdgeNode {
    int v, n;
} E[N * 2];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

// f[u][j][0]: 从 u 出发，在 u 的子树内走 j 步，最后停在任意位置，最多经过多少节点
// f[u][j][1]: 从 u 出发，在 u 的子树内走 j 步，最后回到 u，最多经过多少节点
int f[N][N][2];

void dfs(int u, int fa) {
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs(v, u);
            for (int j = m; j >= 1; j--) {
                // k 必须从 0 开始，否则漏掉“只访问当前子树 v”的情况
                for (int k = 0; k < j; k++) {
                    // 先回到 u，再进入 v，最后停在 v 子树内
                    f[u][j][0] = std::max(f[u][j][0], f[u][k][1] + f[v][j - k - 1][0]);
                    if (j - k - 2 >= 0) {
                        // 先去 v 子树并回到 u，再按旧状态走，最后停任意位置
                        f[u][j][0] = std::max(f[u][j][0], f[u][k][0] + f[v][j - k - 2][1]);
                        // 处理完已合并子树回到 u，再去 v 子树并回到 u
                        f[u][j][1] = std::max(f[u][j][1], f[u][k][1] + f[v][j - k - 2][1]);
                    }
                }
            }
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
        add(a, b), add(b, a);
    }
    // 一步不走时只能访问自己
    for (int i = 0; i < n; i++) {
        f[i][0][0] = f[i][0][1] = 1;
    }
    dfs(0, -1);
    int res = 0;
    // 0 表示“停在任意位置”，正是题目要求的最终状态
    for (int i = 0; i <= m; i++) {
        res = std::max(res, f[0][i][0]);
    }
    std::cout << res << '\n';
    return 0;
}
