#include <algorithm>
#include <cmath>
#include <iostream>

using LL = long long;

const int N = int(1e5) + 5;

int T;
int n, m;
LL A[N];
struct TreeNode {
    LL v;
    bool tag;  // 区间是否全为 1（已稳定，无需再更新）
} tr[N * 4];

void pushup(int u, int L, int R) {
    tr[u].v = tr[u * 2].v + tr[u * 2 + 1].v;
    // 隐含条件：所有 Ei >= 1，因此 sum == len 等价于区间全 1
    tr[u].tag = tr[u].v == R - L + 1;
}

void build(int u, int L, int R) {
    if (L == R) {
        tr[u] = {A[L], A[L] == 1};
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
    pushup(u, L, R);
}

void update(int u, int L, int R, int l, int r) {
    // 剪枝：区间已全为 1，开方无意义
    if (tr[u].tag && L >= l && R <= r) {
        return;
    }
    if (L == R) {
        tr[u].v = static_cast<LL>(sqrt(tr[u].v));
        tr[u].tag = tr[u].v == R - L + 1;
        return;
    }

    int mid = (L + R) / 2;
    if (l <= mid) {
        update(u * 2, L, mid, l, r);
    }
    if (r > mid) {
        update(u * 2 + 1, mid + 1, R, l, r);
    }
    pushup(u, L, R);
}

LL query(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].v;
    }

    int mid = (L + R) / 2;
    LL res = 0;
    if (l <= mid) {
        res += query(u * 2, L, mid, l, r);
    }
    if (r > mid) {
        res += query(u * 2 + 1, mid + 1, R, l, r);
    }
    return res;
}

void solve() {
    std::cout << "Case #" << ++T << ":" << '\n';
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    build(1, 1, n);
    std::cin >> m;
    while (m--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        // 本题数据不保证 X <= Y，必须交换
        if (l > r) {
            std::swap(l, r);
        }
        if (op == 0) {
            update(1, 1, n, l, r);
        } else {
            std::cout << query(1, 1, n, l, r) << '\n';
        }
    }
    // 题目要求每组测试用例后跟一个空行
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n) {
        solve();
    }

    return 0;
}
