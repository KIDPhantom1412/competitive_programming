#include <algorithm>
#include <iostream>
#include <vector>

const int N = int(2e5) + 5, M = int(4e6) + 10;

int n, m;
int A[N];
std::vector<int> disc;

int find(int x) { // 从1开始
    return std::lower_bound(disc.begin(), disc.end(), x) - disc.begin() + 1;
}

int root[N];
struct TreeNode {
    int l, r;
    int sum;
} tr[M];
int cnt; // 动态开点

int build(int L, int R) {
    int cur = ++cnt;
    tr[cur] = {L, R, 0};
    if (L == R) {
        return cur;
    }

    int mid = (L + R) / 2;
    tr[cur].l = build(L, mid);
    tr[cur].r = build(mid + 1, R);
    return cur;
}

int update(int pre, int L, int R, int x) {
    int cur = ++cnt;
    tr[cur].l = tr[pre].l;
    tr[cur].r = tr[pre].r;
    tr[cur].sum = tr[pre].sum + 1;
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

// u = root[l-1]，v = root[r]，利用前缀和差分查询第 k 小
int query(int u, int v, int L, int R, int k) {
    if (L == R) {
        // 叶子直接返回 L：重复元素共享同一排名，到达叶子时 k 可能大于 1
        return L;
    }

    int mid = (L + R) / 2;
    int ls = tr[tr[v].l].sum - tr[tr[u].l].sum;
    if (k <= ls) {
        return query(tr[u].l, tr[v].l, L, mid, k);
    } else {
        return query(tr[u].r, tr[v].r, mid + 1, R, k - ls);
    }
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        disc.push_back(A[i]);
    }

    std::sort(disc.begin(), disc.end());
    disc.erase(std::unique(disc.begin(), disc.end()), disc.end());

    // 这里无需build，l或r等于0时代表没有子节点
    for (int i = 1; i <= n; i++) {
        root[i] = update(root[i - 1], 1, disc.size(), find(A[i]));
    }

    while (m--) {
        int l, r, k;
        std::cin >> l >> r >> k;
        // query 返回离散化后的排名，需用 disc[rank - 1] 映射回原值
        std::cout << disc[query(root[l - 1], root[r], 1, disc.size(), k) - 1] << '\n';
    }

    return 0;
}
