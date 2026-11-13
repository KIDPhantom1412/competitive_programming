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

    // 最小的 mid 个做谷，最大的 mid+1 个做峰；第 j 个谷两侧是 A[n-mid+j-1] 和 A[n-mid+j]
    auto check = [&](int mid) -> bool {
        int i = n - mid, j = 1, cnt = 0;
        while (j <= mid && A[i] > A[j] && A[i + 1] > A[j]) {
            cnt++;
            i++;
            j++;
        }
        return cnt == mid;
    };
    // 谷不能相邻，两端也不能是谷，上界是 floor((n-1)/2)
    int l = 0, r = (n - 1) / 2;
    while (l < r) {
        int mid = (l + r + 1) / 2;
        if (check(mid)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }
    std::cout << l << '\n';
    // 峰谷交替：A[n-l] A[1] A[n-l+1] A[2] ... A[n-1] A[l]
    for (int i = n - l, j = 1; j <= l; j++, i++) {
        std::cout << A[i] << ' ' << A[j] << ' ';
    }
    // 最后一个峰是 A[n]；后面还有中间值时，这里的空格不能省
    std::cout << A[n] << ' ';
    for (int i = l + 1; i < n - l; i++) {
        std::cout << A[i] << ' ';
    }
    std::cout << '\n';
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
