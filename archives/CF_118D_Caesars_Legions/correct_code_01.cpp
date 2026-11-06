#include <cstring>
#include <iostream>

const int MOD = int(1e8);

int n1, n2, k1, k2;
// memo[j][k][l1][l2]：
// j 为末尾连续步兵数，k 为末尾连续骑兵数（两者至多一个非零），
// l1、l2 为剩余步兵 / 骑兵数。
// 已放置总数由 (n1-l1)+(n2-l2) 唯一确定，无需额外维度。
int memo[15][15][110][110];

void add(int& a, int b) {
    a = (a + b) % MOD;
}

int dfs(int j, int k, int l1, int l2) {
    if (l1 == 0 && l2 == 0) {
        return 1;
    }
    int& m = memo[j][k][l1][l2];
    if (m != -1) {
        return m;
    }

    int res = 0;
    // 放步兵：延续步兵段（j+1<=k1 且末尾无骑兵），或从骑兵段末尾新开一段
    if (l1 > 0 && ((j + 1 <= k1 && k == 0) || (j == 0 && k <= k2))) {
        add(res, dfs(j + 1, 0, l1 - 1, l2));
    }
    // 放骑兵：与放步兵对称
    if (l2 > 0 && ((k + 1 <= k2 && j == 0) || (k == 0 && j <= k1))) {
        add(res, dfs(0, k + 1, l1, l2 - 1));
    }

    return m = res;
}

void solve() {
    std::cin >> n1 >> n2 >> k1 >> k2;
    memset(memo, -1, sizeof(memo));
    std::cout << dfs(0, 0, n1, n2) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}
