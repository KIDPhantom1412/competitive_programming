#include <algorithm>
#include <iostream>

const int N = int(5e4) + 5;

int n, m;

struct TreeNode {
    int pre, suf; // 区间最左/最右连续存活段长度
} tr[N * 4];

int stk[N], top; // 记录 D 操作的位置，用于 R 操作

// 合并左右子树信息
void pull(int u, int L, int R) {
    int lc = u * 2, rc = u * 2 + 1;
    int mid = (L + R) / 2;

    tr[u].pre = tr[lc].pre;
    tr[u].suf = tr[rc].suf;

    if (tr[lc].pre == mid - L + 1) {
        tr[u].pre += tr[rc].pre; // 左子树全为 1
    }
    if (tr[rc].suf == R - mid) {
        tr[u].suf += tr[lc].suf; // 右子树全为 1
    }
}

// 初始全部为 1
void build(int u, int L, int R) {
    if (L == R) {
        tr[u] = {1, 1};
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid);
    build(u * 2 + 1, mid + 1, R);
    pull(u, L, R);
}

// 单点修改：位置 p 设为 d（0 表示摧毁，1 表示修复）
void update(int u, int L, int R, int p, int d) {
    if (L == R && L == p) {
        tr[u] = {d, d};
        return;
    }

    int mid = (L + R) / 2;
    if (p <= mid) {
        update(u * 2, L, mid, p, d);
    } else {
        update(u * 2 + 1, mid + 1, R, p, d);
    }
    pull(u, L, R);
}

// 查询位置 p 所在连续存活段的长度
int query(int u, int L, int R, int p) {
    if (L == R && L == p) {
        return tr[u].pre;
    }

    int mid = (L + R) / 2;
    int lc = u * 2, rc = u * 2 + 1;
    int res = 0;

    if (p <= mid) {
        // 若 p 被左子树的右后缀覆盖，则跨左右子树
        if (mid - tr[lc].suf < p) {
            res = tr[lc].suf + tr[rc].pre;
        } else {
            res = query(lc, L, mid, p);
        }
    } else {
        // 若 p 被右子树的左前缀覆盖，则跨左右子树
        if (mid + tr[rc].pre >= p) {
            res = tr[lc].suf + tr[rc].pre;
        } else {
            res = query(rc, mid + 1, R, p);
        }
    }
    return res;
}

void solve() {
    top = 0;
    build(1, 1, n);

    while (m--) {
        std::string op;
        std::cin >> op;

        if (op == "D") {
            int p;
            std::cin >> p;
            stk[++top] = p;
            update(1, 1, n, p, 0);
        } else if (op == "Q") {
            int p;
            std::cin >> p;
            std::cout << query(1, 1, n, p) << '\n';
        } else { // R
            update(1, 1, n, stk[top--], 1);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m) {
        solve();
    }

    return 0;
}
