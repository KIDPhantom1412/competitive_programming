#include <algorithm>
#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    // 上界初值为 a_i 的最大值，下界初值为题目允许的最小 x。
    int mx = int(1e8), mn = 0;
    for (int i = 1; i <= n - 1; i++) {
        if (A[i] < A[i + 1]) {
            // 升序对：x <= floor((A[i] + A[i + 1]) / 2)。
            mx = std::min(mx, (A[i] + A[i + 1]) / 2);
        } else if (A[i] > A[i + 1]) {
            // 降序对：x >= ceil((A[i] + A[i + 1]) / 2)，故加 1 再整除。
            mn = std::max(mn, (A[i] + A[i + 1] + 1) / 2);
        }
        // 相等时不产生任何约束。
    }
    if (mn <= mx) {
        // 下界本身即满足全部约束。
        std::cout << mn << '\n';
    } else {
        std::cout << -1 << '\n';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
