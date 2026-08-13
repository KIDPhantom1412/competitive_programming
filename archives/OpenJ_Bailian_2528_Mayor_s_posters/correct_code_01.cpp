#include <algorithm>
#include <iostream>
#include <vector>

const int N = int(4e4) + 5;

int n;
int A[N], B[N];
std::vector<int> disc;

struct TreeNode {
    int d; // 区间赋值标记：0 表示颜色不统一/无颜色
} tr[N * 4];

void pushdown(int u) {
    if (tr[u].d) {
        tr[u * 2].d = tr[u * 2 + 1].d = tr[u].d;
        tr[u].d = 0;
    }
}

void build(int u, int L, int R) {
    tr[u] = {0};
    if (L >= R) {
        return;
    }
    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
}

void set(int u, int L, int R, int l, int r, int v) {
    if (L >= l && R <= r) {
        tr[u].d = v;
        return;
    }

    pushdown(u);
    int mid = (L + R) / 2;
    if (l <= mid) {
        set(u * 2, L, mid, l, r, v);
    }
    if (r > mid) {
        set(u * 2 + 1, mid + 1, R, l, r, v);
    }
}

int cnt;
bool st[N];

void sum(int u, int L, int R) {
    if (tr[u].d) { // 该节点颜色统一，直接统计
        if (!st[tr[u].d]) {
            st[tr[u].d] = true;
            cnt++;
        }
        return;
    }
    if (L == R) { // 叶子节点且无颜色，必须在这里返回，否则会越界/死递归
        return;
    }

    pushdown(u);
    int mid = (L + R) / 2;
    sum(u * 2, L, mid), sum(u * 2 + 1, mid + 1, R);
}

int find(int x) {
    return std::lower_bound(disc.begin(), disc.end(), x) - disc.begin() + 1;
}

void solve() {
    disc.clear();
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i] >> B[i];
        disc.push_back(A[i]);
        disc.push_back(B[i]);
    }

    std::sort(disc.begin(), disc.end());
    disc.erase(std::unique(disc.begin(), disc.end()), disc.end());

    // 在相邻但不相邻的端点之间插入代表点，防止空区间被错误合并
    int t = disc.size();
    for (int i = 1; i < t; i++) {
        if (disc[i] != disc[i - 1] + 1) {
            disc.push_back(disc[i - 1] + 1);
        }
    }
    std::sort(disc.begin(), disc.end());

    build(1, 1, disc.size());
    for (int i = 1; i <= n; i++) {
        set(1, 1, disc.size(), find(A[i]), find(B[i]), i);
    }

    cnt = 0;
    std::fill_n(st, N, false);
    sum(1, 1, disc.size());
    std::cout << cnt << '\n';
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
