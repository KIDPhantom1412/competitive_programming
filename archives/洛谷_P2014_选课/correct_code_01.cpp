#include <algorithm>
#include <iostream>

const int N = 310, INF = int(1e5);

int n, m;
int W[N];      // W[u]：节点 u 的学分（根节点 0 的学分为 0）
int H[N];      // 邻接表头指针
struct EdgeNode {
    int v, n;  // v：子节点，n：下一条边
} E[N];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int size[N];   // size[u]：以 u 为根的子树大小
int pos[N], cnt;  // pos[i]：DFS 后序第 i 个节点；cnt：总节点数（含根 0）

// DFS 后序遍历，计算子树大小并记录 DFS 序
void dfs(int u) {
    size[u] = 1;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        dfs(v);
        size[u] += size[v];
    }
    pos[++cnt] = u;
}

int f[N][N];   // f[i][j]：考虑前 i 个 DFS 序节点，共选 j 个节点的最大价值

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int a, b;
        std::cin >> a >> b;  // a：先修课，b：学分
        add(a, i);            // a -> i 建立先修关系边
        W[i] = b;
    }

    dfs(0);  // 从虚拟根节点 0 开始 DFS

    // 关键：f[i][0] 必须全部初始化为 0，否则无法表示“从当前节点开始新选子树”的合法中间状态
    for (int i = 0; i <= cnt; i++) {
        std::fill_n(f[i], m + 2, -INF);
        f[i][0] = 0;
    }

    // 树形背包：在 DFS 序上做“选或不选子树”的转移
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= m + 1; j++) {
            f[i][j] = std::max(
                f[i - 1][j - 1] + W[pos[i]],      // 选 pos[i]，从前一个位置转移
                f[i - size[pos[i]]][j]             // 不选 pos[i]，跳过整个子树
            );
        }
    }

    // 根节点 0 必选，占用 1 个名额，所以答案为 f[cnt][m+1]
    std::cout << f[cnt][m + 1] << '\n';
    return 0;
}
