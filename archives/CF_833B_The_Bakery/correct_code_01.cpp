#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

void solve() {
    int n, K;
    std::cin >> n >> K;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }

    std::vector<int> f(n + 1); // f[i] = 当前层把前 i 个分成 j 段的最大价值和
    struct TreeNode {
        int v, d;
    };
    std::vector<TreeNode> tr((n + 1) * 4);
    auto pull = [&](int u) -> void { tr[u].v = std::max(tr[u * 2].v, tr[u * 2 + 1].v); };
    auto build = [&](this auto&& build, int u, int L, int R) -> void {
        tr[u].d = 0; // 关键：每层重建时必须清空懒标记，否则上一层残留的标记会污染本层
        if (L == R) {
            tr[u].v = f[L];
            return;
        }

        int mid = (L + R) / 2;
        build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
        pull(u);
    };
    auto push = [&](int u) -> void {
        if (tr[u].d) {
            int lc = u * 2, rc = u * 2 + 1;
            tr[lc].v += tr[u].d, tr[rc].v += tr[u].d;
            tr[lc].d += tr[u].d, tr[rc].d += tr[u].d;
            tr[u].d = 0;
        }
    };
    auto update = [&](this auto&& update, int u, int L, int R, int l, int r, int d) -> void {
        if (L >= l && R <= r) {
            tr[u].v += d, tr[u].d += d;
            return;
        }

        push(u);
        int mid = (L + R) / 2;
        if (l <= mid) {
            update(u * 2, L, mid, l, r, d);
        }
        if (r > mid) {
            update(u * 2 + 1, mid + 1, R, l, r, d);
        }
        pull(u);
    };
    auto query = [&](this auto&& query, int u, int L, int R, int l, int r) -> int {
        if (L >= l && R <= r) {
            return tr[u].v;
        }

        push(u);
        int mid = (L + R) / 2;
        int res = 0;
        if (l <= mid) {
            res = std::max(res, query(u * 2, L, mid, l, r));
        }
        if (r > mid) {
            res = std::max(res, query(u * 2 + 1, mid + 1, R, l, r));
        }
        return res;
    };

    // 第 1 层：f[i] = 前缀 1..i 的不同种类数
    std::unordered_set<int> S;
    for (int i = 1; i <= n; i++) {
        S.insert(A[i]);
        f[i] = S.size();
    }
    for (int j = 2; j <= K; j++) {
        std::vector<int> last(n + 1, 1); // last[v] = v 上一次出现的位置，初值 1 等价于「未出现」
        build(1, 1, n);
        for (int i = j; i <= n; i++) {
            update(1, 1, n, last[A[i]], i - 1, 1); // 切点 k >= last[A[i]] 的区间新增一种蛋糕
            f[i] = query(1, 1, n, j - 1, i - 1);   // f[j][i] = max dp[j-1][k] + distinct(k+1..i)
            last[A[i]] = i;
        }
    }

    std::cout << f[n] << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    while (t--) {
        solve();
    }

    return 0;
}
