#include <algorithm>
#include <iostream>

using LL = long long;

const int N = 2060;

int n, m;
// t1 = D, t2 = -(i*D), t3 = -(j*D), t4 = i*j*D（D 为二维差分数组）
LL t1[N][N], t2[N][N], t3[N][N], t4[N][N];

void update(LL tr[N][N], int x, int y, LL d) {
    for (int i = x; i <= n; i += i & -i) {
        for (int j = y; j <= m; j += j & -j) {
            tr[i][j] += d;
        }
    }
}

LL sum(LL tr[N][N], int x, int y) {
    LL res = 0;
    for (int i = x; i; i -= i & -i) {
        for (int j = y; j; j -= j & -j) {
            res += tr[i][j];
        }
    }
    return res;
}

// A 的前缀和 S(x,y) = (x+1)(y+1)*ΣD - (y+1)*Σ(i*D) - (x+1)*Σ(j*D) + Σ(i*j*D)
// 由于 t2、t3 存的是相反数，公式中这两项取 + 号
LL sum(int x, int y) {
    return (x + 1) * (y + 1) * sum(t1, x, y) + (y + 1) * sum(t2, x, y) + (x + 1) * sum(t3, x, y) +
           sum(t4, x, y);
}

// 矩形加转化为对差分数组 D 的 4 个角点更新，同步维护 i*D、j*D、i*j*D
void update(int a, int b, int c, int d, LL delta) {
    update(t1, a, b, delta);
    update(t1, a, d + 1, -delta);
    update(t1, c + 1, b, -delta);
    update(t1, c + 1, d + 1, delta);

    update(t2, a, b, -a * delta);
    update(t2, a, d + 1, a * delta);
    update(t2, c + 1, b, (c + 1) * delta);
    update(t2, c + 1, d + 1, -(c + 1) * delta);

    update(t3, a, b, -b * delta);
    update(t3, a, d + 1, (d + 1) * delta);
    update(t3, c + 1, b, b * delta);
    update(t3, c + 1, d + 1, -(d + 1) * delta);

    update(t4, a, b, a * b * delta);
    update(t4, a, d + 1, -a * (d + 1) * delta);
    update(t4, c + 1, b, -(c + 1) * b * delta);
    update(t4, c + 1, d + 1, (c + 1) * (d + 1) * delta);
}

LL sum(int a, int b, int c, int d) {
    return sum(c, d) - sum(a - 1, d) - sum(c, b - 1) + sum(a - 1, b - 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string op;
    std::cin >> op >> n >> m;
    while (std::cin >> op) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        if (op == "L") {
            LL delta;
            std::cin >> delta;
            update(a, b, c, d, delta);
        } else {
            std::cout << sum(a, b, c, d) << '\n';
        }
    }

    return 0;
}
