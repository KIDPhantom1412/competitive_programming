#include <algorithm>
#include <cstdint>
#include <iostream>

void solve() {
    int64_t A[3];
    for (int i = 0; i < 3; i++) {
        std::cin >> A[i];
    }
    std::sort(A, A + 3);
    if (A[2] >= (A[0] + A[1]) * 2) {
        // a 桌 (1,0,2) 与 b 桌 (0,1,2)。
        std::cout << A[0] + A[1] << '\n';
    } else {
        // 丢掉总数模 3 的余数后，可拆成 t 张合法桌子，见题解。
        std::cout << (A[0] + A[1] + A[2]) / 3 << '\n';
    }
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
