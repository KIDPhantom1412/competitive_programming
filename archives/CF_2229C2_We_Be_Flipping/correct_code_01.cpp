#include <cstdlib>
#include <iostream>

using LL = long long;

const int N = int(2e5) + 5;

int n;
int A[N];
LL ps[N], ss[N];
int res[N], cnt;

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        ps[i] = ps[i - 1] + std::abs(A[i]); // 前缀绝对值之和
    }
    ss[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        ss[i] = ss[i + 1] + A[i]; // 后缀原值和
    }

    // 不操作时总和为 ss[1]；选 last=i 时总和为 ps[i-1] - A[i] + ss[i+1]
    LL mx = ss[1];
    int last = 0;
    for (int i = 1; i <= n; i++) {
        if (A[i] > 0 && ps[i - 1] - A[i] + ss[i + 1] > mx) {
            mx = ps[i - 1] - A[i] + ss[i + 1];
            last = i;
        }
    }

    // 先把 [1, last) 全部变成负数（从右往左，当前为正就操作），再操作 last
    cnt = 0;
    bool flipped = false; // 已被更大下标的操作翻转过奇数次
    for (int i = last - 1; i >= 1; i--) {
        if (flipped ? A[i] < 0 : A[i] > 0) { // 当前值为正
            res[cnt++] = i;
            flipped = !flipped;
        }
    }
    if (last) {
        res[cnt++] = last;
    }

    std::cout << cnt << '\n';
    for (int i = 0; i < cnt; i++) {
        std::cout << res[i] << ' ';
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
