#include <algorithm>
#include <cstdio>
#include <iostream>

const int N = 1010, M = N * (N - 1);

int H[N];
struct EdgeNode {
    int v, n;
} E[M];
int idx;

void add(int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

int root;
int ts;
int cut[N];
int dfn[N], low[N];
int sub[N], ans[N]; // sub：满足 low[v] >= dfn[u] 的儿子个数；ans：所属 DFS 树的根

void dfs(int u, int fa) {
    dfn[u] = low[u] = ++ts;
    ans[u] = root;
    int cnt = 0;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (v != fa) {
            if (!dfn[v]) {
                cnt++;
                dfs(v, u);
                low[u] = std::min(low[u], low[v]);

                if (low[v] >= dfn[u]) {
                    // 非根点有一个这样的儿子即为割点；根需要至少两个儿子
                    if (u != root || cnt >= 2) {
                        cut[u] = 1;
                    }

                    // v 的子树整体成为一个独立连通块
                    sub[u]++;
                }
            } else {
                low[u] = std::min(low[u], dfn[v]);
            }
        }
    }
}

void solve() {
    ts = 0;
    std::fill_n(cut, N, 0);
    std::fill_n(dfn, N, 0);
    std::fill_n(low, N, 0);
    std::fill_n(sub, N, 0);
    std::fill_n(ans, N, 0);

    for (int i = 1; i <= 1000; i++) {
        if (!dfn[i]) {
            root = i;
            dfs(root, -1);
        }
    }

    int sum = 0;
    for (int i = 1; i <= 1000; i++) {
        if (cut[i]) {
            // 非 DFS 树根：除子树方向的块外，还有与父亲同属的那一块
            int res = sub[i] + (ans[i] != i ? 1 : 0);
            printf("  SPF node %d leaves %d subnets\n", i, res);
        }
        sum += cut[i];
    }
    if (!sum) {
        std::cout << "  No SPF nodes" << '\n';
    }
    std::cout << '\n';
}

int main() {
    int t = 0;
    while (true) {
        idx = 0;
        std::fill_n(H, N, 0);
        int a, b;
        while (std::cin >> a && a) {
            std::cin >> b;
            add(a, b), add(b, a);
        }
        if (idx == 0) {
            break;
        }
        std::cout << "Network #" << ++t << '\n';
        solve();
    }

    return 0;
}
