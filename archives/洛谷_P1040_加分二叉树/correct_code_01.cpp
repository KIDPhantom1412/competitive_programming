#include <algorithm>
#include <iostream>

using LL = long long;

const int N = 35;

int n;
LL f[N][N];      // f[l][r]：区间 [l,r] 子树的最大加分
int root[N][N];  // root[l][r]：区间 [l,r] 取得最大加分时的根节点

// 记忆化搜索求区间 [l,r] 的最大加分
LL dfs(int l, int r) {
    if (l > r) {
        return 1;  // 空子树加分为 1
    }
    if (f[l][r] > 0) {
        return f[l][r];  // 已计算过，直接返回
    }
    for (int i = l; i <= r; i++) {
        LL lt = dfs(l, i - 1);       // 左子树最大加分
        LL rt = dfs(i + 1, r);       // 右子树最大加分
        LL cur = lt * rt + f[i][i];  // 左×右 + 根的分数
        if (cur > f[l][r]) {
            f[l][r] = cur;
            root[l][r] = i;
        }
    }
    return f[l][r];
}

// 按 root 表递归输出前序遍历
void print(int l, int r) {
    if (l > r) {
        return;
    }
    std::cout << root[l][r] << ' ';
    print(l, root[l][r] - 1);
    print(root[l][r] + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> f[i][i];
        root[i][i] = i;  // 单个节点的子树根就是自己
    }

    std::cout << dfs(1, n) << '\n';
    print(1, n);

    return 0;
}
