#include <algorithm>
#include <iostream>

using LL = long long;

const int N = int(5e5) + 5;
const LL INF = LL(1e14);

int n, m;
int A[N];
struct TreeNode {
    LL sum;
    LL mx1, mx2, mxb; // 最大值、次大值、历史最大值
    int cnt;          // 最大值个数
    LL da, db;        // 非最大值集合加法标记与其历史最大
    LL mxda, mxdb;    // 最大值集合加法标记与其历史最大
} tr[N * 4];

void pushup(int u) {
    int lc = u * 2, rc = u * 2 + 1;
    tr[u].sum = tr[lc].sum + tr[rc].sum;
    tr[u].mx1 = std::max(tr[lc].mx1, tr[rc].mx1);
    tr[u].mxb = std::max(tr[lc].mxb, tr[rc].mxb);
    if (tr[lc].mx1 > tr[rc].mx1) {
        tr[u].cnt = tr[lc].cnt;
        tr[u].mx2 = std::max(tr[lc].mx2, tr[rc].mx1);
    } else if (tr[lc].mx1 < tr[rc].mx1) {
        tr[u].cnt = tr[rc].cnt;
        tr[u].mx2 = std::max(tr[lc].mx1, tr[rc].mx2);
    } else {
        tr[u].cnt = tr[lc].cnt + tr[rc].cnt;
        tr[u].mx2 = std::max(tr[lc].mx2, tr[rc].mx2);
    }
}

void build(int u, int L, int R) {
    if (L == R) {
        tr[u] = {A[L], A[L], -INF, A[L], 1, 0, 0, 0, 0};
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
    pushup(u);
}

// 打标记：先算历史最大（用旧的 da/mxda），再累加
void pushTag(int u, int L, int R, LL da, LL db, LL mxda, LL mxdb) {
    tr[u].sum += mxda * tr[u].cnt + da * (R - L + 1 - tr[u].cnt);
    tr[u].mxb = std::max(tr[u].mxb, tr[u].mx1 + mxdb);
    tr[u].mx1 += mxda;
    if (tr[u].mx2 != -INF) {
        tr[u].mx2 += da;
    }
    tr[u].db = std::max(tr[u].db, tr[u].da + db);
    tr[u].da += da;
    tr[u].mxdb = std::max(tr[u].mxdb, tr[u].mxda + mxdb);
    tr[u].mxda += mxda;
}

void pushdown(int u, int L, int R) {
    int mid = (L + R) / 2;
    int lc = u * 2, rc = u * 2 + 1;
    // 父节点剔除自身标记后的底层最大值；子节点 mx1 已含自身标记，不能再减 mxda[child]
    LL mx1u = tr[u].mx1 - tr[u].mxda;
    if (tr[lc].mx1 == mx1u) {
        pushTag(lc, L, mid, tr[u].da, tr[u].db, tr[u].mxda, tr[u].mxdb);
    } else {
        pushTag(lc, L, mid, tr[u].da, tr[u].db, tr[u].da, tr[u].db);
    }
    if (tr[rc].mx1 == mx1u) {
        pushTag(rc, mid + 1, R, tr[u].da, tr[u].db, tr[u].mxda, tr[u].mxdb);
    } else {
        pushTag(rc, mid + 1, R, tr[u].da, tr[u].db, tr[u].da, tr[u].db);
    }
    // 下传后必须清空父节点标记
    tr[u].da = tr[u].db = tr[u].mxda = tr[u].mxdb = 0;
}

LL querySum(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].sum;
    }

    pushdown(u, L, R);
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

LL queryMaxA(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].mx1;
    }

    pushdown(u, L, R);
    int mid = (L + R) / 2;
    LL res = -INF;
    if (l <= mid) {
        res = std::max(res, queryMaxA(u * 2, L, mid, l, r));
    }
    if (r > mid) {
        res = std::max(res, queryMaxA(u * 2 + 1, mid + 1, R, l, r));
    }
    return res;
}

LL queryMaxB(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].mxb;
    }

    pushdown(u, L, R);
    int mid = (L + R) / 2;
    LL res = -INF;
    if (l <= mid) {
        res = std::max(res, queryMaxB(u * 2, L, mid, l, r));
    }
    if (r > mid) {
        res = std::max(res, queryMaxB(u * 2 + 1, mid + 1, R, l, r));
    }
    return res;
}

void add(int u, int L, int R, int l, int r, LL d) {
    if (L >= l && R <= r) {
        tr[u].sum += d * (R - L + 1);
        tr[u].mx1 += d;
        if (tr[u].mx2 != -INF) {
            tr[u].mx2 += d;
        }
        tr[u].mxb = std::max(tr[u].mxb, tr[u].mx1);
        tr[u].da += d;
        tr[u].mxda += d;
        // 历史最大标记 = max(旧值, 累加后的新标记)
        tr[u].db = std::max(tr[u].db, tr[u].da);
        tr[u].mxdb = std::max(tr[u].mxdb, tr[u].mxda);
        return;
    }

    pushdown(u, L, R);
    int mid = (L + R) / 2;
    if (l <= mid) {
        add(u * 2, L, mid, l, r, d);
    }
    if (r > mid) {
        add(u * 2 + 1, mid + 1, R, l, r, d);
    }
    pushup(u);
}

void chMin(int u, int L, int R, int l, int r, LL d) {
    if (d >= tr[u].mx1) {
        return;
    }
    if (L >= l && R <= r) {
        if (d > tr[u].mx2) {
            // 只有最大值集合受影响：以负增量并入最大值加法标记
            tr[u].sum -= (tr[u].mx1 - d) * tr[u].cnt;
            tr[u].mxda -= (tr[u].mx1 - d);
            tr[u].mx1 = d;
            return;
        }
    }
    if (L == R) {
        tr[u].mx1 = std::min(tr[u].mx1, d);
        tr[u].sum = tr[u].mx1;
        return;
    }

    pushdown(u, L, R);
    int mid = (L + R) / 2;
    if (l <= mid) {
        chMin(u * 2, L, mid, l, r, d);
    }
    if (r > mid) {
        chMin(u * 2 + 1, mid + 1, R, l, r, d);
    }
    pushup(u);
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
            add(1, 1, n, l, r, d);
        } else if (op == 2) {
            LL d;
            std::cin >> d;
            chMin(1, 1, n, l, r, d);
        } else if (op == 3) {
            std::cout << querySum(1, 1, n, l, r) << '\n';
        } else if (op == 4) {
            std::cout << queryMaxA(1, 1, n, l, r) << '\n';
        } else if (op == 5) {
            std::cout << queryMaxB(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}
