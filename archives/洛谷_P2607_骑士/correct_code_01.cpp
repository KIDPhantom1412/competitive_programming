#include <algorithm>
#include <cstring>
#include <iostream>

using LL = long long;

const int N = int(1e6) + 5;

int n;
int attack[N];  // 每个骑士的战斗力
int H[N];       // 邻接表头
struct EdgeNode {
    int v, n;   // v：目标节点，n：下一条边的编号
} E[N * 2];
int idx = 1;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

bool st[N];   // 节点是否已被 findCircle 访问
struct Circle {
    int x, y;
    bool exists;
} circle;

// 在基环树中找环，删除一条环边。找到后用 v=-1 标记已删除。
void findCircle(int u, int fa) {
    st[u] = true;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        // 跳过父节点回边，以及已经删除的边（v == -1）
        if (v != fa && v != -1) {
            if (st[v]) {
                circle = {u, v, true};        // 记录环边 (u, v)
                E[i].v = E[i ^ 1].v = -1;     // 双向删除该环边
            } else {
                findCircle(v, u);
            }
        }
    }
}

LL f[N][2];  // f[u][0]：不选 u；f[u][1]：选 u

// 树形 DP：求以 u 为根的子树的最大权独立集
void dfs(int u, int fa) {
    f[u][0] = 0;
    f[u][1] = attack[u];
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != -1 && v != fa) {       // 只走树边
            dfs(v, u);
            f[u][0] += std::max(f[v][0], f[v][1]);
            f[u][1] += f[v][0];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        std::cin >> a >> b;
        attack[i] = a;
        add(i, b), add(b, i);  // 无向图建边
    }

    LL res = 0;
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {            // 每个未访问的节点开启一个新连通块
            circle = {0, 0, false};
            findCircle(i, -1);
            if (circle.exists) {
                int x = circle.x, y = circle.y;
                dfs(x, -1);
                LL mx = f[x][0];    // 强制 x 不选
                dfs(y, -1);
                mx = std::max(mx, f[y][0]);  // 强制 y 不选，取较大值
                res += mx;
            } else {             // 该连通块无环，是一棵纯树
                dfs(i, -1);
                res += std::max(f[i][0], f[i][1]);
            }
        }
    }

    std::cout << res << '\n';
    return 0;
}
