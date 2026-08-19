#include <algorithm>
#include <iostream>

const int N = int(1e5) + 5;

int n, m;
struct TreeNode {
    int l, r;
    int pre0, suf0, mx0;  // 全 0 的前缀 / 后缀 / 最长连续长度
    int pre1, suf1, mx1;  // 全 1 的前缀 / 后缀 / 最长连续长度
    int sum;              // 1 的个数
    int op;               // 懒标记：-1 无，0 赋 0，1 赋 1，2 翻转

    void flip() {
        std::swap(pre0, pre1);
        std::swap(suf0, suf1);
        std::swap(mx0, mx1);
        sum = r - l + 1 - sum;
    }

    void set(int v) {
        int zero = v ^ 1, one = v;
        pre0 = suf0 = mx0 = (r - l + 1) * zero;
        pre1 = suf1 = mx1 = (r - l + 1) * one;
        sum = (r - l + 1) * one;
    }
} tr[N * 4];
int A[N];

void pull(int u) {
    int lc = u * 2, rc = u * 2 + 1;
    tr[u].sum = tr[lc].sum + tr[rc].sum;
    tr[u].mx0 = std::max({tr[lc].mx0, tr[rc].mx0, tr[lc].suf0 + tr[rc].pre0});
    tr[u].mx1 = std::max({tr[lc].mx1, tr[rc].mx1, tr[lc].suf1 + tr[rc].pre1});
    tr[u].pre0 = tr[lc].pre0, tr[u].suf0 = tr[rc].suf0;
    if (tr[lc].pre0 == tr[lc].r - tr[lc].l + 1) {
        tr[u].pre0 += tr[rc].pre0;
    }
    if (tr[rc].suf0 == tr[rc].r - tr[rc].l + 1) {
        tr[u].suf0 += tr[lc].suf0;
    }
    tr[u].pre1 = tr[lc].pre1, tr[u].suf1 = tr[rc].suf1;
    if (tr[lc].pre1 == tr[lc].r - tr[lc].l + 1) {
        tr[u].pre1 += tr[rc].pre1;
    }
    if (tr[rc].suf1 == tr[rc].r - tr[rc].l + 1) {
        tr[u].suf1 += tr[lc].suf1;
    }
}

void build(int u, int L, int R) {
    tr[u].l = L, tr[u].r = R;
    tr[u].op = -1;
    if (L == R) {
        int zero = A[L] ^ 1, one = A[L];
        tr[u] = {L, R, zero, zero, zero, one, one, one, one, -1};
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
    pull(u);
}

void pushTag(int u, int op) {
    if (op != 2) {
        tr[u].set(op);
        tr[u].op = op;
    } else {
        tr[u].flip();
        if (tr[u].op == -1) {
            tr[u].op = op;
        } else if (tr[u].op != 2) {
            tr[u].op ^= 1;
        } else {
            tr[u].op = -1;
        }
    }
}

void push(int u) {
    // 只有存在懒标记时才下传，下传后清空
    if (tr[u].op >= 0) {
        int lc = u * 2, rc = u * 2 + 1;
        pushTag(lc, tr[u].op);
        pushTag(rc, tr[u].op);
        tr[u].op = -1;
    }
}

void update(int u, int l, int r, int op) {
    if (tr[u].l >= l && tr[u].r <= r) {
        pushTag(u, op);
        return;
    }

    push(u);
    int mid = (tr[u].l + tr[u].r) / 2;
    if (l <= mid) {
        update(u * 2, l, r, op);
    }
    if (r > mid) {
        update(u * 2 + 1, l, r, op);
    }
    pull(u);
}

int querySum(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return tr[u].sum;
    }

    push(u);
    int mid = (tr[u].l + tr[u].r) / 2;
    int res = 0;
    if (l <= mid) {
        res += querySum(u * 2, l, r);
    }
    if (r > mid) {
        res += querySum(u * 2 + 1, l, r);
    }
    return res;
}

struct Node {
    int len;  // 返回区间长度，用于合并前缀 / 后缀
    int pre, suf, mx;
};

Node queryMax(int u, int l, int r) {
    if (tr[u].l >= l && tr[u].r <= r) {
        return {tr[u].r - tr[u].l + 1, tr[u].pre1, tr[u].suf1, tr[u].mx1};
    }

    push(u);
    int mid = (tr[u].l + tr[u].r) / 2;
    Node left{-1, -1, -1, -1}, right{-1, -1, -1, -1};
    if (l <= mid) {
        left = queryMax(u * 2, l, r);
    }
    if (r > mid) {
        right = queryMax(u * 2 + 1, l, r);
    }
    if (left.mx == -1 || right.mx == -1) {
        return left.mx == -1 ? right : left;
    }
    Node res{left.len + right.len, left.pre, right.suf, std::max(left.mx, right.mx)};
    if (left.pre == left.len) {
        res.pre += right.pre;
    }
    if (right.suf == right.len) {
        res.suf += left.suf;
    }
    res.mx = std::max(res.mx, left.suf + right.pre);
    return res;
}

void solve() {
    std::cin >> n >> m;
    for (int i = 0; i < n; i++) {
        std::cin >> A[i];
    }
    build(1, 0, n - 1);  // 题目下标为 0-based
    while (m--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op >= 0 && op <= 2) {
            update(1, l, r, op);
        } else if (op == 3) {
            std::cout << querySum(1, l, r) << '\n';
        } else {
            std::cout << queryMax(1, l, r).mx << '\n';
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
