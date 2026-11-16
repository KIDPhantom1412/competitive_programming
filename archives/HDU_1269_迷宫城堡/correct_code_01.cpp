#include <algorithm>
#include <iostream>
#include <vector>

const int N = int(1e4) + 5, M = int(1e5) + 5;

int n, m;
int H[N], rH[N];
struct EdgeNode {
    int v, n;
} E[M * 2]; // 原图和反图共用边池，每条通道占两条边
int idx;

void add(int H[], int a, int b) {
    E[++idx] = {b, H[a]}, H[a] = idx;
}

bool st[N];
std::vector<int> order;

// 原图 DFS，递归返回前记入结束序
void dfs1(int u) {
    st[u] = true;
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (!st[v]) {
            dfs1(v);
        }
    }
    order.push_back(u);
}

int cnt;
int scc[N];

// 反图 DFS，从当前起点走出一个强连通分量
void dfs2(int u) {
    st[u] = true;
    scc[u] = cnt;
    for (int i = rH[u]; i; i = E[i].n) {
        int v = E[i].v;
        if (!st[v]) {
            dfs2(v);
        }
    }
}

void solve() {
    idx = 0;
    std::fill_n(H, N, 0);
    std::fill_n(rH, N, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        std::cin >> a >> b;
        add(H, a, b);
        add(rH, b, a);
    }

    std::fill_n(st, N, false);
    order.clear();
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            dfs1(i);
        }
    }

    std::fill_n(st, N, false);
    cnt = 0;
    // 按结束序逆序在反图上启动，每个新起点对应一个分量
    for (auto it = order.rbegin(); it != order.rend(); it++) {
        if (!st[*it]) {
            cnt++;
            dfs2(*it);
        }
    }

    std::cout << (cnt == 1 ? "Yes" : "No") << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m, n || m) {
        solve();
    }

    return 0;
}
