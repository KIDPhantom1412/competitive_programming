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
    std::sort(A.begin() + 1, A.end());

    // dup：出现至少两次的不同值个数；single：只出现一次的不同值个数
    int dup = 0, single = 0;
    for (int i = 1; i <= n;) {
        int j = i;
        while (j <= n && A[j] == A[i]) { // 扫描一段相等的值
            j++;
        }
        if (j - i == 1) {
            single++;
        } else {
            dup++;
        }
        i = j;
    }
    // 答案 = dup + ceil(single / 2)
    std::cout << dup + (single + 1) / 2 << '\n';
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
