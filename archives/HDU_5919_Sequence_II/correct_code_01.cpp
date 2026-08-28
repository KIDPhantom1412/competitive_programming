// HDU 5919 Sequence II
// 可持久化线段树：root[i] 维护后缀 [i,n] 中每个值首次出现的位置
// 查询 [l,r]：在 root[l] 中统计 <= r 的位置数得 k，再树上二分第 (k+1)/2 小的位置
#include <algorithm>
#include <iostream>

const int N = int(2e5) + 5;

int T;
int n, m;
int A[N];

int root[N];
struct TreeNode {
    int l, r;
    int sum;
} tr[N * 40];  // 最坏约 2n*log2(n) ≈ 7.2e6 个节点
int cnt;

int update(int pre, int L, int R, int x, int d) {
    int cur = ++cnt;
    tr[cur] = tr[pre];
    tr[cur].sum += d;
    if (L == R) {
        return cur;
    }

    int mid = (L + R) / 2;
    if (x <= mid) {
        tr[cur].l = update(tr[pre].l, L, mid, x, d);
    } else {
        tr[cur].r = update(tr[pre].r, mid + 1, R, x, d);
    }
    return cur;
}

// root[v] 相对 root[u] 在 [l,r] 内的位置数（u 取空树 root[n+1]）
int querySum(int u, int v, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[v].sum - tr[u].sum;
    }

    int mid = (L + R) / 2;
    int res = 0;
    if (l <= mid) {
        res += querySum(tr[u].l, tr[v].l, L, mid, l, r);
    }
    if (r > mid) {
        res += querySum(tr[u].r, tr[v].r, mid + 1, R, l, r);
    }
    return res;
}

// root[v] 相对 root[u] 的第 k 小位置；注意 ls 必须取左右「子节点」之差
int queryKth(int u, int v, int L, int R, int k) {
    if (L == R) {
        return L;
    }

    int mid = (L + R) / 2;
    int ls = tr[tr[v].l].sum - tr[tr[u].l].sum;  // 左子树和，勿写成 tr[v].sum - tr[u].sum
    if (k <= ls) {
        return queryKth(tr[u].l, tr[v].l, L, mid, k);
    } else {
        return queryKth(tr[u].r, tr[v].r, mid + 1, R, k - ls);
    }
    return -1;
}

int ht[N];  // ht[v]：值 v 当前最近一次出现的位置（从右往左扫）

void solve() {
    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }

    cnt = 0;
    std::fill_n(ht, N, 0);
    std::fill_n(root, N, 0);
    for (int i = n; i >= 1; i--) {
        if (!ht[A[i]]) {
            root[i] = update(root[i + 1], 1, n, i, 1);
        } else {
            // 值已出现：删旧位置，插新位置，保持「每值只留首次出现」
            int t = update(root[i + 1], 1, n, ht[A[i]], -1);
            root[i] = update(t, 1, n, i, 1);
        }
        ht[A[i]] = i;
    }

    int res = 0;  // res 即 ans_{i-1}，每个查询后必须更新（强制在线）
    std::cout << "Case #" << ++T << ":";
    while (m--) {
        int l, r;
        std::cin >> l >> r;
        l = (res + l) % n + 1;
        r = (res + r) % n + 1;
        if (l > r) {
            std::swap(l, r);
        }
        int k = querySum(root[n + 1], root[l], 1, n, 1, r);  // 区间不同数个数
        k = (k + 1) / 2;                                     // ceil(k/2)
        res = queryKth(root[n + 1], root[l], 1, n, k);
        std::cout << ' ' << res;
    }
    std::cout << '\n';
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
