#include <algorithm>
#include <iostream>

const int N = int(5e4) + 5;

int n, m;                    // n 为序列长度，m 为询问数量
int A[N];                    // 排列
int st[N];                   // st[d] 表示当前扫描中 d 的倍数最近出现的位置
int tr[N];                   // 树状数组，维护前缀最大值

// 树状数组单点更新：在位置 x 维护最大值 v
void update(int x, int v) {
    for (int i = x; i <= n; i += i & -i) {
        tr[i] = std::max(tr[i], v);
    }
}

// 树状数组前缀查询：查询 [1, x] 的最大值
int query(int x) {
    int res = 0;
    for (int i = x; i; i -= i & -i) {
        res = std::max(res, tr[i]);
    }
    return res;
}

struct Query {
    int i, l, r;

    bool operator<(const Query& ct) const {
        return l < ct.l;  // 按左端点升序，配合从右往左扫描使用
    }
} Q[N];
int res[N];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        std::cin >> l >> r;
        Q[i] = {i, l, r};
    }

    std::sort(Q + 1, Q + 1 + m);           // 按左端点排序
    std::fill_n(tr, n + 1, 0);             // 清空树状数组
    std::fill_n(st, n + 1, 0);             // 清空因子最近出现位置

    // 从右向左扫描位置 i
    for (int i = n, j = m; i >= 1; i--) {
        // 枚举 A[i] 的所有因子
        for (int k = 1; k * k <= A[i]; k++) {
            if (A[i] % k == 0) {
                int d1 = k;
                int d2 = A[i] / k;

                // 如果 d1 之前出现过，则在它的最近位置更新最大 gcd 值
                if (st[d1]) {
                    update(st[d1], d1);
                }
                st[d1] = i;

                // 两个因子相同时只处理一次，避免重复更新
                if (d2 != d1) {
                    if (st[d2]) {
                        update(st[d2], d2);
                    }
                    st[d2] = i;
                }
            }
        }

        // 处理所有左端点恰好为 i 的询问
        while (j >= 1 && i == Q[j].l) {
            res[Q[j].i] = query(Q[j].r);
            j--;
        }
        if (j == 0) {
            break;
        }
    }

    for (int i = 1; i <= m; i++) {
        std::cout << res[i] << '\n';
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
