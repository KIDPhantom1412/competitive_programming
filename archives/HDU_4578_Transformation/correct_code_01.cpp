#include <algorithm>
#include <iostream>

const int N = int(1e5) + 5, MOD = int(1e4) + 7;

int n, m;

struct TreeNode {
    int L, R;
    int v1, v2, v3;   // 分别维护 sum(a_i), sum(a_i^2), sum(a_i^3)
    int add, mul, set; // 懒标记：加法、乘法、赋值

    void updateAdd(int d) {
        d %= MOD;
        v3 = (v3 + (R - L + 1) * d % MOD * d % MOD * d % MOD + 3 * v2 * d % MOD +
              3 * v1 * d % MOD * d % MOD) %
             MOD;
        v2 = (v2 + 2 * v1 * d % MOD + (R - L + 1) * d % MOD * d % MOD) % MOD;
        v1 = (v1 + (R - L + 1) * d % MOD) % MOD;
        add = (add + d) % MOD;
    }

    void updateMul(int d) {
        d %= MOD;
        v1 = v1 * d % MOD;
        v2 = v2 * d % MOD * d % MOD;
        v3 = v3 * d % MOD * d % MOD * d % MOD;
        add = add * d % MOD;
        mul = mul * d % MOD;
    }

    void updateSet(int d) {
        v1 = (R - L + 1) * d % MOD;
        v2 = v1 * d % MOD;
        v3 = v2 * d % MOD;
        set = d;
        add = 0;
        mul = 1;
    }
} tr[N * 4];

void pushup(int u) {
    int lc = u * 2, rc = u * 2 + 1;
    tr[u].v1 = (tr[lc].v1 + tr[rc].v1) % MOD;
    tr[u].v2 = (tr[lc].v2 + tr[rc].v2) % MOD;
    tr[u].v3 = (tr[lc].v3 + tr[rc].v3) % MOD;
}

void pushdown(int u) {
    int lc = u * 2, rc = u * 2 + 1;
    if (tr[u].set) {                // 隐含条件：题目保证 c >= 1，set 不会为 0
        tr[lc].updateSet(tr[u].set);
        tr[rc].updateSet(tr[u].set);
        tr[u].set = 0;
    }
    if (tr[u].mul != 1) {
        tr[lc].updateMul(tr[u].mul);
        tr[rc].updateMul(tr[u].mul);
        tr[u].mul = 1;
    }
    if (tr[u].add) {
        tr[lc].updateAdd(tr[u].add);
        tr[rc].updateAdd(tr[u].add);
        tr[u].add = 0;
    }
}

void build(int u, int L, int R) {
    tr[u] = {L, R, 0, 0, 0, 0, 1, 0};
    if (L >= R) {
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
}

void add(int u, int l, int r, int d) {
    if (tr[u].L >= l && tr[u].R <= r) {
        tr[u].updateAdd(d);
        return;
    }
    pushdown(u);
    int mid = (tr[u].L + tr[u].R) / 2;
    if (l <= mid) {
        add(u * 2, l, r, d);
    }
    if (r > mid) {
        add(u * 2 + 1, l, r, d);
    }
    pushup(u);
}

void mul(int u, int l, int r, int d) {
    if (tr[u].L >= l && tr[u].R <= r) {
        tr[u].updateMul(d);
        return;
    }
    pushdown(u);
    int mid = (tr[u].L + tr[u].R) / 2;
    if (l <= mid) {
        mul(u * 2, l, r, d);
    }
    if (r > mid) {
        mul(u * 2 + 1, l, r, d);
    }
    pushup(u);
}

void set(int u, int l, int r, int d) {
    if (tr[u].L >= l && tr[u].R <= r) {
        tr[u].updateSet(d);
        return;
    }
    pushdown(u);
    int mid = (tr[u].L + tr[u].R) / 2;
    if (l <= mid) {
        set(u * 2, l, r, d);
    }
    if (r > mid) {
        set(u * 2 + 1, l, r, d);
    }
    pushup(u);
}

int query(int u, int l, int r, int p) {
    if (tr[u].L >= l && tr[u].R <= r) {
        if (p == 1) {
            return tr[u].v1;
        } else if (p == 2) {
            return tr[u].v2;
        } else {
            return tr[u].v3;
        }
    }
    pushdown(u); // 查询部分覆盖的节点前必须下放懒标记
    int res = 0, mid = (tr[u].L + tr[u].R) / 2;
    if (l <= mid) {
        res = (res + query(u * 2, l, r, p)) % MOD;
    }
    if (r > mid) {
        res = (res + query(u * 2 + 1, l, r, p)) % MOD;
    }
    return res;
}

void solve() {
    build(1, 1, n);
    while (m--) {
        int op, l, r, d;
        std::cin >> op >> l >> r >> d;
        if (op == 1) {
            add(1, l, r, d);
        } else if (op == 2) {
            mul(1, l, r, d);
        } else if (op == 3) {
            set(1, l, r, d);
        } else {
            std::cout << query(1, l, r, d) << '\n';
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n >> m, n || m) {
        solve();
    }

    return 0;
}
