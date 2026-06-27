#include <algorithm>
#include <climits>
#include <iostream>

const int N = 16010;

int n;
int W[N];          // 每个节点的权值（美丽指数）
int H[N];          // 邻接表头指针
struct EdgeNode {
    int v, n;      // v：目标节点，n：下一条边的索引
} E[N * 2];
int idx;           // 边计数器

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int res = INT_MIN;

// 返回以 u 为根、必须保留 u 的连通子树的最大权值和
int dfs(int u, int fa) {
    int sum = W[u];
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            int t = dfs(v, u);
            if (t > 0) {      // 子树贡献为正才保留，否则剪掉该边
                sum += t;
            }
        }
    }
    res = std::max(res, sum); // 维护全局最大子树和
    return sum;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> W[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        std::cin >> a >> b;
        add(a, b), add(b, a); // 无向树建边
    }
    dfs(1, -1);
    std::cout << res << '\n';
    return 0;
}
