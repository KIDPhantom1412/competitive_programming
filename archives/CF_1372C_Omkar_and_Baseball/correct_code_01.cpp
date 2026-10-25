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
    // 剥掉尾部已经就位的后缀：A[n] == n 表示位置 n 已归位
    while (n >= 1 && A[n] == n) {
        n--;
    }
    // 跳过头部已经就位的前缀
    int i = 1;
    while (i <= n && A[i] == i) {
        i++;
    }
    // 剩余区间 [i, n] 的两端都是错位位置
    int res = 0;
    if (i <= n) {
        res = 1;
        for (; i <= n; i++) {
            if (A[i] == i) { // 区间内夹着就位位置，一次交换无法完成
                res = 2;
                break;
            }
        }
    }
    std::cout << res << '\n';
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
