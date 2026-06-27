#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

const int N = 2510;
const double INF = 1e9;

int n, m;
int A[N], B[N];      // A[i] = P_i（战斗值），B[i] = S_i（费用）
double V[N];         // V[i] = P_i - mid * S_i
int H[N];
struct EdgeNode {
    int v, n;
} E[N];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int size[N];
int pos[N], cnt;

// DFS 后序遍历，同时计算每棵子树大小
void dfs(int u) {
    size[u] = 1;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        dfs(v);
        size[u] += size[v];
    }
    pos[++cnt] = u;
}

double f[N][N];

// 判断是否存在选 K 人的方案，使得 sum(P) - mid * sum(S) > 0
bool check(double mid) {
    for (int i = 0; i <= cnt; i++) {
        std::fill_n(f[i] + 1, m, -INF);
    }
    for (int i = 1; i <= n; i++) {
        V[i] = A[i] - mid * B[i];
    }
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j <= m; j++) {
            // 选 pos[i]：子树其余节点已处理完
            // 不选 pos[i]：整棵子树跳过
            f[i][j] = std::max(f[i - 1][j - 1] + V[pos[i]],
                               f[i - size[pos[i]]][j]);
        }
    }
    return f[cnt][m] > 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin >> m >> n;
    m++; // JYY 必选，占一个名额
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        A[i] = b, B[i] = a;
        add(c, i); // 注意：父节点 c 指向子节点 i
    }
    dfs(0);
    double l = 0, r = 1e4;
    while (r - l > 1e-7) {
        double mid = (l + r) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    printf("%.3lf\n", l);
    return 0;
}
