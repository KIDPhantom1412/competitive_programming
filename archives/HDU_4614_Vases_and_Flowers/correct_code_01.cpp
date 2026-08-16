#include <algorithm>
#include <iostream>

const int N = int(1e5) + 5;

int n, m;
struct TreeNode {
    int v, d;
    bool tag;
} tr[N * 4];

void pull(int u) {
    tr[u].v = tr[u * 2].v + tr[u * 2 + 1].v;
}

void push(int u, int L, int R) {
    if (tr[u].tag) {
        int mid = (L + R) / 2;
        int lc = u * 2, rc = u * 2 + 1;
        tr[lc].v = (mid - L + 1) * tr[u].d, tr[rc].v = (R - mid) * tr[u].d;
        tr[lc].d = tr[rc].d = tr[u].d;
        tr[lc].tag = tr[rc].tag = true;
        tr[u].tag = false;
    }
}

void build(int u, int L, int R) {
    tr[u] = {};
    if (L >= R) {
        return;
    }

    int mid = (L + R) / 2;
    build(u * 2, L, mid), build(u * 2 + 1, mid + 1, R);
}

void set(int u, int L, int R, int l, int r, int v) {
    if (L >= l && R <= r) {
        tr[u].v = (R - L + 1) * v;
        tr[u].d = v;
        tr[u].tag = true;
        return;
    }

    push(u, L, R);
    int mid = (L + R) / 2;
    if (l <= mid) {
        set(u * 2, L, mid, l, r, v);
    }
    if (r > mid) {
        set(u * 2 + 1, mid + 1, R, l, r, v);
    }
    pull(u);
}

int query(int u, int L, int R, int l, int r) {
    if (L >= l && R <= r) {
        return tr[u].v;
    }

    push(u, L, R);
    int res = 0, mid = (L + R) / 2;
    if (l <= mid) {
        res += query(u * 2, L, mid, l, r);
    }
    if (r > mid) {
        res += query(u * 2 + 1, mid + 1, R, l, r);
    }
    return res;
}

int findFirstEmpty(int start) {
    int l = start, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        int remainEmpty = mid - start + 1 - query(1, 1, n, start, mid);
        if (remainEmpty >= 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int findLastEmpty(int start, int cnt) {
    int l = start, r = n;
    while (l < r) {
        int mid = (l + r) / 2;
        int remainEmpty = mid - start + 1 - query(1, 1, n, start, mid);
        if (remainEmpty >= cnt) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

void solve() {
    std::cin >> n >> m;
    build(1, 1, n);
    while (m--) {
        int op, a, b;
        std::cin >> op >> a >> b;
        if (op == 1) {
            a++;
            int remainEmpty = n - a + 1 - query(1, 1, n, a, n);
            if (!remainEmpty) {
                std::cout << "Can not put any one." << '\n';
            } else {
                b = std::min(b, remainEmpty);
                int l = findFirstEmpty(a), r = findLastEmpty(a, b);
                std::cout << l - 1 << ' ' << r - 1 << '\n';
                set(1, 1, n, l, r, 1);
            }
        } else {
            a++, b++;
            std::cout << query(1, 1, n, a, b) << '\n';
            set(1, 1, n, a, b, 0);
        }
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
