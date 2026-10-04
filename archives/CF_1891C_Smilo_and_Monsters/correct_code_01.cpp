#include <algorithm>
#include <iostream>

using LL = long long;

const int N = int(2e5) + 5;

int n;
int A[N];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    std::sort(A + 1, A + 1 + n);
    LL res = 0;
    LL x = 0;
    int i = 1, j = n;
    // 普攻打最小堆，大招打最大堆。始终保持 x <= A[j]。
    while (i < j) {
        if (A[i] <= A[j] - x) {
            // 最小堆整堆拿去普攻，连击仍不超过最大堆。
            x += A[i];
            res += A[i];
            i++;
        } else {
            // 再普攻 A[j] - x 次，连击刚好等于最大堆，大招把它清掉。
            res += A[j] - x + 1;
            A[i] -= A[j] - x;
            j--;
            x = 0;
        }
    }
    if (A[i]) {
        // 只剩一堆：ceil((A[i] - x) / 2) 次普攻；还能放大招时再加 1 次。
        LL first = (A[i] - x + 1) / 2;
        res += first;
        if (A[i] - first > 0) {
            res++;
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
