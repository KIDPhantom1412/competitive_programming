#include <algorithm>
#include <iostream>
#include <vector>

const int N = 5010;

int n;

std::vector<int> xs;

int find(int x) {
    return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

struct Line {
    int y;
    int x1, x2;
    int d;

    bool operator<(const Line& ct) const {
        return y < ct.y;
    }
} line[N * 2];

// len: 区间总长度；v: 被覆盖长度；cnt: 连续覆盖段数
// lb/rb: 左右端点是否被覆盖；d: 覆盖次数
struct TreeNode {
    int len, v, cnt;
    bool lb, rb;
    int d;
} tr[N * 2 * 4];
int A[N * 2];

void pull(int u, int L, int R) {
    int lc = u * 2, rc = u * 2 + 1;
    if (L < R) {
        tr[u].len = tr[lc].len + tr[rc].len;
    }
    if (tr[u].d) {
        tr[u].v = tr[u].len;
        tr[u].cnt = 1;
        tr[u].lb = tr[u].rb = true;
    } else {
        if (L < R) {
            tr[u].v = tr[lc].v + tr[rc].v;
            tr[u].cnt = tr[lc].cnt + tr[rc].cnt;
            tr[u].lb = tr[lc].lb, tr[u].rb = tr[rc].rb;
            // 左右子树在交界处都覆盖时，合并为一段
            if (tr[lc].rb && tr[rc].lb) {
                tr[u].cnt--;
            }
        } else {
            tr[u].v = tr[u].cnt = 0;
            tr[u].lb = tr[u].rb = false;
        }
    }
}

void build(int u, int L, int R) {
    tr[u].v = tr[u].d = tr[u].cnt = 0;
    tr[u].lb = tr[u].rb = false;
    if (L == R) {
        tr[u].len = A[L];
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
    pull(u, L, R);
}

void update(int u, int L, int R, int l, int r, int d) {
    if (L >= l && R <= r) {
        tr[u].d += d;
        pull(u, L, R);
        return;
    }

    int mid = (L + R) / 2;
    if (l <= mid) {
        update(u * 2, L, mid, l, r, d);
    }
    if (r > mid) {
        update(u * 2 + 1, mid + 1, R, l, r, d);
    }
    pull(u, L, R);
}

int queryLength() {
    return tr[1].v;
}

int queryCount() {
    return tr[1].cnt;
}

void solve() {
    int cnt = 0;
    xs.clear();
    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        xs.push_back(x1);
        xs.push_back(x2);
        line[++cnt] = {y1, x1, x2, 1};   // 下边：进入
        line[++cnt] = {y2, x1, x2, -1};  // 上边：离开
    }

    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    for (int i = 1; i < (int)xs.size(); i++) {
        A[i] = xs[i] - xs[i - 1];  // 离散化后第 i 段的实际长度
    }
    build(1, 1, (int)xs.size() - 1);

    std::sort(line + 1, line + 1 + cnt);

    int res = 0, preLen = 0;
    for (int i = 1; i <= cnt; i++) {
        auto [y, x1, x2, d] = line[i];
        // 竖边贡献：连续段数 × 2 × 扫描高度差
        res += queryCount() * 2 * (y - line[i - 1].y);
        update(1, 1, (int)xs.size() - 1, find(x1) + 1, find(x2), d);
        // 横边贡献：覆盖长度变化量
        res += std::abs(queryLength() - preLen);
        preLen = queryLength();
    }

    std::cout << res << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n) {
        solve();
    }

    return 0;
}
