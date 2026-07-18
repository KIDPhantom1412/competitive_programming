#include <algorithm>
#include <cstring>
#include <iostream>

const int N = int(5e4) + 5;

int n;
int sd[N]; // 真约数之和（不包含自身）
int H[N];  // 邻接表头
struct EdgeNode {
    int v, n;
} E[N];

void add(int a, int b) {
    static int idx;
    E[++idx] = {b, H[a]}, H[a] = idx; // 从 sd[i] 向 i 连边
}

bool st[N];
int res;

// 返回从 u 出发向下的最长链长度
int dfs(int u) {
    st[u] = true;
    int d1 = 0, d2 = 0; // 最长链、次长链
    for (int i = H[u]; i; i = E[i].n) {
        int v = E[i].v;
        int d = dfs(v) + 1; // 经过 u-v 这条边的最长链
        if (d > d1) {
            d2 = d1;
            d1 = d;
        } else if (d > d2) {
            d2 = d;
        }
    }
    res = std::max(res, d1 + d2); // 以 u 为最高点的直径候选
    return d1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;

    // 筛法求每个数的真约数之和
    for (int i = 1; i <= n; i++) {
        for (int j = 2; j <= n / i; j++) {
            sd[i * j] += i;
        }
    }

    // 若 sd[i] < i，则 i 与 sd[i] 可互相转换，建一条从 sd[i] 到 i 的边
    for (int i = 1; i <= n; i++) {
        if (sd[i] < i) {
            add(sd[i], i);
        }
    }

    // 对每个尚未访问的树根做 DFS，求整片森林的直径最大值
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            dfs(i);
        }
    }

    std::cout << res << '\n';

    return 0;
}
