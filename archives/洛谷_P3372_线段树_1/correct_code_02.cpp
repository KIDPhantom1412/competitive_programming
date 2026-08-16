#include <algorithm>
#include <iostream>

using LL = long long;

const int N = int(1e5) + 5;

int n, m;
LL A[N];

struct TreeNode {
    LL v, d; // v: 区间和, d: 懒标记（区间未下传的增量）
} tr[N * 4];

void pull(int u) {
    tr[u].v = tr[u * 2].v + tr[u * 2 + 1].v;
}

void build(int u, int L, int R) {
    if (L == R) {
        tr[u] = {A[L], 0};
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
    pull(u);
}

void push(int u, int L, int R) { // 需要 L, R 计算子区间长度
    if (tr[u].d) {
        int mid = (L + R) / 2;
        tr[u * 2].v += (mid - L + 1) * tr[u].d, tr[u * 2].d += tr[u].d;
        tr[u * 2 + 1].v += (R - mid) * tr[u].d, tr[u * 2 + 1].d += tr[u].d;
        tr[u].d = 0; // 下传后必须清空
    }
}

void update(int u, int L, int R, int l, int r, LL d) {
    if (L >= l && R <= r) {
        tr[u].v += (R - L + 1) * d, tr[u].d += d; // 区间和要乘区间长度
        return;
    }

    push(u, L, R);
    int mid = (L + R) / 2;
    if (l <= mid) { // 有交集才递归
        update(u * 2, L, mid, l, r, d);
    }
    if (r > mid) {
        update(u * 2 + 1, mid + 1, R, l, r, d);
    }
    pull(u); // 递归回来必须重算父节点
}

LL query(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].v;
    }

    push(u, L, R);
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    build(1, 1, n);

    while (m--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op == 1) {
            LL d;
            std::cin >> d;
            update(1, 1, n, l, r, d);
        } else {
            std::cout << query(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}
