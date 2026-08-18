#include <algorithm>
#include <iostream>

const int N = int(5e4) + 5;

int n, m;
struct TreeNode {
    int pre, suf, mx;  // 左端连续空房前缀、右端连续空房后缀、区间最长连续空房段
    bool tag;          // 懒标记：整个区间被统一置为空(1)或占用(0)
} tr[N * 4];

// 合并左右子树信息
void pull(int u, int L, int R) {
    int lc = u * 2, rc = u * 2 + 1;
    int mid = (L + R) / 2;
    tr[u].pre = tr[lc].pre, tr[u].suf = tr[rc].suf;
    if (tr[lc].pre == mid - L + 1) {        // 左子树全空
        tr[u].pre += tr[rc].pre;
    }
    if (tr[rc].suf == R - mid) {            // 右子树全空
        tr[u].suf += tr[lc].suf;
    }
    tr[u].mx = std::max({tr[lc].mx, tr[rc].mx, tr[lc].suf + tr[rc].pre});
}

// 建树，初始所有房间为空
void build(int u, int L, int R) {
    if (L == R) {
        tr[u] = {1, 1, 1, false};
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
    pull(u, L, R);
}

// 下传懒标记
void push(int u, int L, int R) {
    if (tr[u].tag) {
        int lc = u * 2, rc = u * 2 + 1;
        int mid = (L + R) / 2;
        int empty = tr[u].mx == (R - L + 1);  // 当前节点全空则为 1，否则为 0
        tr[lc].pre = tr[lc].suf = tr[lc].mx = (mid - L + 1) * empty;
        tr[rc].pre = tr[rc].suf = tr[rc].mx = (R - mid) * empty;
        tr[lc].tag = tr[rc].tag = true;
        tr[u].tag = false;
    }
}

// 区间置空(d=1)或占用(d=0)
void set(int u, int L, int R, int l, int r, int d) {
    if (L >= l && R <= r) {
        tr[u].mx = tr[u].pre = tr[u].suf = (R - L + 1) * d;
        tr[u].tag = true;
        return;
    }

    push(u, L, R);
    int mid = (L + R) / 2;
    if (l <= mid) {
        set(u * 2, L, mid, l, r, d);
    }
    if (r > mid) {
        set(u * 2 + 1, mid + 1, R, l, r, d);
    }
    pull(u, L, R);
}

// 查询最靠左的连续 len 个空房的起始位置
int query(int u, int L, int R, int len) {
    if (len > tr[u].mx) {
        return 0;
    }

    int mid = (L + R) / 2;
    int lc = u * 2, rc = u * 2 + 1;
    push(u, L, R);
    if (int ret = query(lc, L, mid, len); ret) {  // 优先左子树
        return ret;
    }
    if (tr[lc].suf + tr[rc].pre >= len) {          // 跨中点
        return mid - tr[lc].suf + 1;
    }
    if (int ret = query(rc, mid + 1, R, len); ret) {  // 再右子树
        return ret;
    }
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    build(1, 1, n);
    while (m--) {
        int op;
        std::cin >> op;
        if (op == 1) {
            int len;
            std::cin >> len;
            int ret = query(1, 1, n, len);
            std::cout << ret << '\n';
            if (ret) {
                set(1, 1, n, ret, ret + len - 1, 0);  // 占用
            }
        } else {
            int l, len;
            std::cin >> l >> len;
            set(1, 1, n, l, l + len - 1, 1);          // 清空
        }
    }

    return 0;
}
