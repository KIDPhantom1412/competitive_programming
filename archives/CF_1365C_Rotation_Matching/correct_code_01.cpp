#include <algorithm>
#include <iostream>
#include <unordered_map>

const int N = int(2e5) + 5;
int A[N], B[N];

int mod(int a, int m) {
    // 将负的位置差也归一化到 [0, m - 1]。
    return (a % m + m) % m;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::unordered_map<int, int> idx;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        // 排列中每个值唯一，记录它在 A 中的位置。
        idx[A[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> B[i];
    }
    std::unordered_map<int, int> cnt;
    for (int i = 1; i <= n; i++) {
        // B 右移这个距离后，B[i] 与 A 中的相同值对齐。
        cnt[mod(idx[B[i]] - i, n)]++;
    }
    int res = 0;
    for (auto [k, v] : cnt) {
        res = std::max(res, v);
    }
    std::cout << res << '\n';

    return 0;
}
