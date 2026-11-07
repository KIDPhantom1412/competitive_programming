#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_set>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }

    // 前缀和相等 <=> 中间子段和为 0，S 记录自上次插入以来的前缀和
    std::unordered_set<int64_t> S{0};
    int64_t sum = 0;
    int res = 0;
    for (int i = 1; i <= n; i++) {
        sum += A[i];
        if (S.find(sum) != S.end()) {
            // 必须以 i 结尾的零和子段存在，在 i-1 与 i 之间插入一个超大数
            res++;
            // 插入后跨缝隙的区间全部被破坏，新段从 A[i] 开始
            S = {0};
            sum = A[i];
        }
        S.insert(sum);
    }
    std::cout << res << '\n';
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
