#include <iostream>
#include <numeric>

const int N = int(1e5) + 5, M = 25;

int n, m;
// f[u][j] = 以 u 为根的子树/整树中，距离 u 恰好为 j 的奶牛数之和
int f[N][M];
int H[N];
struct EdgeNode {
    int v, n;
} E[N * 2];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

// 第一次 DFS：固定根为 1，计算子树内的贡献
void dfs1(int u, int fa) {
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs1(v, u);
            for (int j = 1; j <= m; j++) {
                f[u][j] += f[v][j - 1];
            }
        }
    }
}

// 第二次 DFS：换根，把父亲方向的信息合并进来
void dfs2(int u, int fa) {
    if (fa != -1) {
        // 必须倒序！否则 f[u][j-2] 会用到本轮已经被修改过的值
        for (int j = m; j >= 2; j--) {
            f[u][j] -= f[u][j - 2];
        }
        for (int j = 1; j <= m; j++) {
            f[u][j] += f[fa][j - 1];
        }
    }
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            dfs2(v, u);
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
    // f[i][0] 直接读入每点奶牛数
    for (int i = 1; i <= n; i++) {
        std::cin >> f[i][0];
    }

    dfs1(1, -1);
    dfs2(1, -1);

    for (int i = 1; i <= n; i++) {
        // 距离 0..m 全部累加，注意要包含 f[i][0]
        std::cout << std::accumulate(f[i], f[i] + 1 + m, 0) << '\n';
    }

    return 0;
}
