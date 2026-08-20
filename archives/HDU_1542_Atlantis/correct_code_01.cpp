#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

const int N = 205; // 2n 条扫描线，n <= 100

int T;
int n;

struct Line {
    double y;
    double x1, x2;
    int d;

    bool operator<(const Line& ct) const {
        return y < ct.y;
    }
} line[N];

std::vector<double> xs;

// x 坐标是实数，必须用 double，不能用 int 否则会被截断
int find(double x) {
    return std::lower_bound(xs.begin(), xs.end(), x) - xs.begin();
}

struct TreeNode {
    double v;   // 实际长度
    double len; // 原本长度
    int d;      // tag
} tr[N * 2 * 4];
double A[N];

// 与普通线段树的区别：tag d 表示覆盖层数，不需要 push
// d > 0 时整个区间被覆盖，v = len；否则 v 由子节点决定，叶子为 0
void pull(int u, int L, int R) {
    int lc = u * 2, rc = u * 2 + 1;
    if (L < R) {
        tr[u].len = tr[lc].len + tr[rc].len;
    }
    if (tr[u].d) {
        tr[u].v = tr[u].len;
    } else {
        tr[u].v = L == R ? 0 : tr[lc].v + tr[rc].v;
    }
}

void build(int u, int L, int R) {
    tr[u].v = 0;
    tr[u].d = 0;
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
        tr[u].d += d;      // 增加/减少覆盖层数
        pull(u, L, R);     // 直接 pull，无需 push
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

double query() {
    return tr[1].v;
}

void solve() {
    int cnt = 0;
    xs.clear(); // 每个测试用例清空离散化数组
    for (int i = 1; i <= n; i++) {
        double x1, x2, y1, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        // 每个矩形拆成下边界 (+1) 和上边界 (-1) 两条扫描线
        line[++cnt] = {y1, x1, x2, 1};
        line[++cnt] = {y2, x1, x2, -1};
        xs.push_back(x1);
        xs.push_back(x2);
    }

    // x 坐标离散化
    std::sort(xs.begin(), xs.end());
    xs.erase(std::unique(xs.begin(), xs.end()), xs.end());
    for (size_t i = 1; i < xs.size(); i++) {
        A[i] = xs[i] - xs[i - 1]; // 第 i 个基本区间的长度
    }
    build(1, 1, xs.size() - 1);

    // 按 y 扫描
    std::sort(line + 1, line + 1 + cnt);
    double res = 0;
    for (int i = 1; i <= cnt; i++) {
        // 当前覆盖长度 * 高度差
        res += query() * (line[i].y - line[i - 1].y);
        // 将扫描线对应的 x 区间映射到离散化后的区间 [l, r]
        int l = find(line[i].x1) + 1, r = find(line[i].x2);
        update(1, 1, xs.size() - 1, l, r, line[i].d);
    }
    std::cout << "Test case #" << ++T << '\n';
    std::cout << "Total explored area: " << res << '\n';
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(2);
    while (std::cin >> n, n) {
        solve();
    }

    return 0;
}