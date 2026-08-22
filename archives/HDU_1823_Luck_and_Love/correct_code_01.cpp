#include <algorithm>
#include <iomanip>
#include <iostream>

const int N = 105, M = 1005;

int m;
struct TreeNode1 { // 线段树套线段树
    struct TreeNode2 {
        int mx; // 最大缘分
    } A[M * 4];
} H[N * 4];

void build2(auto* tr, int u, int L, int R) {
    tr[u].mx = -1;
    if (L == R) {
        return;
    }

    int mid = (L + R) / 2;
    build2(tr, u * 2, L, mid), build2(tr, u * 2 + 1, mid + 1, R);
}

void build1(int u, int L, int R) {
    build2(H[u].A, 1, 0, 1000);
    if (L == R) {
        return;
    }

    int mid = (L + R) / 2;
    build1(u * 2, L, mid), build1(u * 2 + 1, mid + 1, R);
}

void update2(auto* tr, int u, int L, int R, int a, int l) {
    tr[u].mx = std::max(tr[u].mx, l);
    if (L == R) {
        return;
    }
    int mid = (L + R) / 2;
    if (a <= mid) {
        update2(tr, u * 2, L, mid, a, l);
    }
    if (a > mid) {
        update2(tr, u * 2 + 1, mid + 1, R, a, l);
    }
}

void update1(int u, int L, int R, int h, int a, int l) {
    update2(H[u].A, 1, 0, 1000, a, l);
    if (L == R) {
        return;
    }
    int mid = (L + R) / 2;
    if (h <= mid) {
        update1(u * 2, L, mid, h, a, l);
    }
    if (h > mid) {
        update1(u * 2 + 1, mid + 1, R, h, a, l);
    }
}

int query2(auto* tr, int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].mx;
    }

    int mid = (L + R) / 2;
    int res = -1;
    if (l <= mid) {
        res = std::max(res, query2(tr, u * 2, L, mid, l, r));
    }
    if (r > mid) {
        res = std::max(res, query2(tr, u * 2 + 1, mid + 1, R, l, r));
    }
    return res;
}

int query1(int u, int L, int R, int hl, int hr, int al, int ar) {
    if (L >= hl && R <= hr) {
        return query2(H[u].A, 1, 0, 1000, al, ar);
    }

    int mid = (L + R) / 2;
    int res = -1;
    if (hl <= mid) {
        res = std::max(res, query1(u * 2, L, mid, hl, hr, al, ar));
    }
    if (hr > mid) {
        res = std::max(res, query1(u * 2 + 1, mid + 1, R, hl, hr, al, ar));
    }
    return res;
}

void solve() {
    build1(1, 100, 200);
    while (m--) {
        std::string op;
        std::cin >> op;
        if (op == "I") {
            int h;
            double a, l;
            std::cin >> h >> a >> l;
            update1(1, 100, 200, h, a * 10, l * 10); // 浮点乘 10 转整数下标
        } else {
            int h1, h2;
            double a1, a2;
            std::cin >> h1 >> h2 >> a1 >> a2;
            if (h1 > h2) { // 不保证区间端点有序
                std::swap(h1, h2);
            }
            if (a1 > a2) {
                std::swap(a1, a2);
            }
            int ret = query1(1, 100, 200, h1, h2, a1 * 10, a2 * 10);
            if (ret == -1) {
                std::cout << -1 << '\n';
            } else {
                std::cout << double(ret) / 10 << '\n';
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cout << std::fixed << std::setprecision(1);
    while (std::cin >> m, m) {
        solve();
    }

    return 0;
}
