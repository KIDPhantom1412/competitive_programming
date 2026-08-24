// HDU 4417 Super Mario
// 主席树（可持久化线段树）：区间 [L,R] 内高度 <= H 的砖块计数
#include <algorithm>
#include <iostream>
#include <vector>

const int N = int(1e5) + 5;

int T;
int n, m;
int A[N];

std::vector<int> disc;

// 返回 <= x 的离散化值个数（即 upper_bound 下标，从 1 开始）
int find(int x) {
    return std::upper_bound(disc.begin(), disc.end(), x) - disc.begin();
}

int root[N];

struct TreeNode {
    int l, r;
    int sum;
} tr[N * 20]; // 关键：主席树需 n * (log2(S)+1) 个节点，最坏约 1.8e6，N*4 会越界
int cnt;

// 在 pre 版本基础上向值域 [L,R] 插入值 x，返回新版本根
int update(int pre, int L, int R, int x) {
    int cur = ++cnt;
    tr[cur] = tr[pre];
    tr[cur].sum++;
    if (L == R) {
        return cur;
    }

    int mid = (L + R) / 2;
    if (x <= mid) {
        tr[cur].l = update(tr[pre].l, L, mid, x);
    } else {
        tr[cur].r = update(tr[pre].r, mid + 1, R, x);
    }
    return cur;
}

// root[v] 与 root[u] 作差，查询值域区间 [l,r] 内的元素个数
int querySum(int u, int v, int L, int R, int l, int r) {
    if (l > r) { // 关键：find(H) 可能为 0，空区间直接返回，否则叶子处无限递归
        return 0;
    }
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

void solve() {
    cnt = 0;
    disc.clear();

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        disc.push_back(A[i]);
    }

    std::sort(disc.begin(), disc.end());
    disc.erase(std::unique(disc.begin(), disc.end()), disc.end());

    for (int i = 1; i <= n; i++) {
        root[i] = update(root[i - 1], 1, disc.size(), find(A[i]));
    }

    std::cout << "Case " << ++T << ":" << '\n';

    while (m--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << querySum(root[l], root[r + 1], 1, disc.size(), 1, find(k)) << '\n';
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
