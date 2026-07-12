#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(1e4) + 5, M = 16;

int n, m;
int H[N];
struct EdgeNode {
    int v, n;
} E[N * 2];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int f[N][M];

void dfs(int u, int fa) {
    // 初始化：u 单独取颜色 j 时的代价为 j
    for (int j = 1; j <= m; j++) {
        f[u][j] = j;
    }
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs(v, u);
            // 枚举 u 的颜色 j
            for (int j = 1; j <= m; j++) {
                int mn = N * M;
                // 子节点 v 不能取颜色 j，取其它颜色中的最小值
                for (int k = 1; k <= m; k++) {
                    if (k != j) {
                        mn = std::min(mn, f[v][k]);
                    }
                }
                f[u][j] += mn;
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        add(a, b), add(b, a);
    }

    // 确定颜色上界 m = ceil(log2 n) + 1
    for (int i = 0;; i++) {
        if ((1 << i) >= n) {
            m = i + 1;
            break;
        }
    }

    dfs(1, -1);

    std::cout << *std::min_element(f[1] + 1, f[1] + 1 + m) << '\n';

    return 0;
}
