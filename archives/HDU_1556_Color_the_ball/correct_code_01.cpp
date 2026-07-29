#include <algorithm>
#include <iostream>

const int N = int(1e5) + 5;

int n;
int tr[N];  // 树状数组，维护差分数组

void update(int x, int d) {
    for (int i = x; i <= n; i += i & -i) {
        tr[i] += d;
    }
}

int sum(int x) {
    int res = 0;
    for (int i = x; i; i -= i & -i) {
        res += tr[i];
    }
    return res;
}

void solve() {
    std::fill(tr, tr + n + 5, 0);
    for (int i = 1; i <= n; i++) {
        int a, b;
        std::cin >> a >> b;
        update(a, 1);       // 差分数组 [a]   +1
        update(b + 1, -1);  // 差分数组 [b+1] -1
    }
    for (int i = 1; i <= n; i++) {
        std::cout << sum(i) << ' ';  // 前缀和即第 i 个气球的涂色次数
    }
    std::cout << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    while (std::cin >> n, n) {  // 多测，读到 0 结束
        solve();
    }

    return 0;
}
