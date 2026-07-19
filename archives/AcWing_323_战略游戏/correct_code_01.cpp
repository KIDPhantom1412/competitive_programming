#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1510; // 节点数上限

int n;              // 当前树的节点数
int H[N];           // 邻接表头指针
struct EdgeNode {
    int v, n;       // v: 目标节点, n: 下一条边的索引
} E[N * 2];         // 无向树，每条边存两次
int idx;            // 边计数器

// 添加无向边 a-b
void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

// f[u][0]: u 不放置士兵时的最小士兵数
// f[u][1]: u 放置士兵时的最小士兵数
int f[N][2];

// 以 u 为根的子树进行树形 DP，fa 为父节点
void dfs(int u, int fa) {
    f[u][0] = 0, f[u][1] = 1; // u 不选贡献 0，选则贡献 1 名士兵
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {               // 避免回到父节点
            dfs(v, u);
            f[u][0] += f[v][1];       // u 不选，子节点必须选
            f[u][1] += std::min(f[v][0], f[v][1]); // u 已选，子节点可选可不选
        }
    }
}

void solve() {
    idx = 0;
    ::memset(H, 0, sizeof(H)); // 清空邻接表

    // 读入 N 行节点信息，格式：u:(m) v1 v2 ...
    for (int i = 0; i < n; i++) {
        int u, m;
        ::scanf("%d:(%d)", &u, &m);
        while (m--) {
            int v;
            ::scanf("%d", &v);
            add(u, v), add(v, u);
        }
    }

    dfs(0, -1); // 以 0 为根 DFS
    std::printf("%d\n", std::min(f[0][0], f[0][1]));
}

int main() {
    // 多组测试数据，直到 EOF
    while (~::scanf("%d", &n)) {
        solve();
    }
    return 0;
}
