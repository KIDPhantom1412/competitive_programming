#include <algorithm>
#include <iostream>

using LL = long long;

const int N = int(1e6) + 5;

int n, m;
struct TreeNode {
    LL sum, mx1, mx2;  // 区间和、最大值、次大值
    int cnt;           // 最大值出现次数
} tr[N * 4];
int A[N];

// 由子节点合并当前节点信息
void pushup(int u) {
    int lc = u * 2, rc = u * 2 + 1;
    tr[u].sum = tr[lc].sum + tr[rc].sum;
    if (tr[lc].mx1 == tr[rc].mx1) {
        tr[u].mx1 = tr[lc].mx1;
        tr[u].cnt = tr[lc].cnt + tr[rc].cnt;
        tr[u].mx2 = std::max(tr[lc].mx2, tr[rc].mx2);
    } else {
        tr[u].mx1 = std::max(tr[lc].mx1, tr[rc].mx1);
        tr[u].cnt = tr[lc].mx1 > tr[rc].mx1 ? tr[lc].cnt : tr[rc].cnt;
        tr[u].mx2 = tr[lc].mx1 > tr[rc].mx1 ? std::max(tr[lc].mx2, tr[rc].mx1)
                                            : std::max(tr[lc].mx1, tr[rc].mx2);
    }
}

// 下传区间 chmin 标记：仅当子节点最大值更大时才更新
void pushdown(int u) {
    int lc = u * 2, rc = u * 2 + 1;
    if (tr[u].mx1 < tr[lc].mx1) {
        tr[lc].sum -= (tr[lc].mx1 - tr[u].mx1) * tr[lc].cnt;
        tr[lc].mx1 = tr[u].mx1;
    }
    if (tr[u].mx1 < tr[rc].mx1) {
        tr[rc].sum -= (tr[rc].mx1 - tr[u].mx1) * tr[rc].cnt;
        tr[rc].mx1 = tr[u].mx1;
    }
}

void build(int u, int L, int R) {
    if (L == R) {
        tr[u] = {A[L], A[L], -1, 1};  // 叶子节点次大值记为 -1
        return;
    }
    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
    pushup(u);
}

// 区间 chmin：将 [l,r] 内的元素与 a 取较小值
void update(int u, int L, int R, int l, int r, LL a) {
    if (a >= tr[u].mx1) {
        return;  // a 不小于当前区间最大值，无需修改
    }
    if (L >= l && R <= r) {
        if (a > tr[u].mx2) {
            // 可以直接把最大值降到 a
            tr[u].sum -= (tr[u].mx1 - a) * tr[u].cnt;
            tr[u].mx1 = a;
            return;
        }
    }

    pushdown(u);
    int mid = (L + R) / 2;
    if (l <= mid) {
        update(u * 2, L, mid, l, r, a);
    }
    if (r > mid) {
        update(u * 2 + 1, mid + 1, R, l, r, a);
    }
    pushup(u);
}

LL queryMax(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].mx1;
    }

    pushdown(u);
    int mid = (L + R) / 2;
    LL res = -1;
    if (l <= mid) {
        res = std::max(res, queryMax(u * 2, L, mid, l, r));
    }
    if (r > mid) {
        res = std::max(res, queryMax(u * 2 + 1, mid + 1, R, l, r));
    }
    return res;
}

LL querySum(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].sum;
    }

    pushdown(u);
    int mid = (L + R) / 2;
    LL res = 0;
    if (l <= mid) {
        res += querySum(u * 2, L, mid, l, r);
    }
    if (r > mid) {
        res += querySum(u * 2 + 1, mid + 1, R, l, r);
    }
    return res;
}

void solve() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    build(1, 1, n);
    while (m--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op == 0) {
            int a;
            std::cin >> a;
            update(1, 1, n, l, r, a);
        } else if (op == 1) {
            std::cout << queryMax(1, 1, n, l, r) << '\n';
        } else {
            std::cout << querySum(1, 1, n, l, r) << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
