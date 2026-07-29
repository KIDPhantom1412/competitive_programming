#include <algorithm>
#include <iostream>

using LL = long long;

const int N = int(1e5) + 5;

int n, m;
LL tr1[N], tr2[N];

void update(LL* tr, int x, LL d) {
    for (int i = x; i <= n; i += i & -i) {
        tr[i] += d;
    }
}

LL sum(LL* tr, int x) {
    LL res = 0;
    for (int i = x; i; i -= i & -i) {
        res += tr[i];
    }
    return res;
}

// 前缀和 P(x) = x * S1(x) - S2(x)
LL sum(int x) {
    return x * sum(tr1, x) - sum(tr2, x);
}

void update(int l, int r, LL d) { // 区间修改：差分 d_l += d, d_{r+1} -= d
    update(tr1, l, d), update(tr1, r + 1, -d);
    update(tr2, l, (l - 1) * d), update(tr2, r + 1, -r * d);
}

LL sum(int l, int r) { // 区间查询
    return sum(r) - sum(l - 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        LL cur;
        std::cin >> cur;
        update(i, i, cur); // 直接建树，不要再手动差分
    }

    for (int i = 0; i < m; i++) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op == 1) {
            LL k; // k 可能超过 int
            std::cin >> k;
            update(l, r, k);
        } else {
            std::cout << sum(l, r) << '\n';
        }
    }

    return 0;
}
