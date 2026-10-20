#include <iostream>
#include <vector>

using LL = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    LL sum = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
        sum += A[i];
    }
    // 三段和相等要求总和能被 3 整除，且每段都非空
    if (sum % 3 || n < 3) {
        std::cout << 0 << '\n';
        return;
    }
    // T = 0 时，去掉末位（前缀必为 0），再在剩余前缀 0 的位置里取两个切点
    if (sum == 0) {
        LL cnt = -1;
        for (int i = 1; i <= n; i++) {
            sum += A[i];
            if (sum == 0) {
                cnt++;
            }
        }
        std::cout << cnt * (cnt - 1) / 2 << '\n';
        return;
    }

    sum /= 3;
    LL cur = 0;
    LL cnt = 0, ans = 0;
    for (int i = 1; i <= n; i++) {
        cur += A[i];
        // 2T 切点必须在已经出现的 T 切点之后，且不能落在末位（第三段非空）
        if (i < n && cur == sum * 2) {
            ans += cnt;
        }
        if (cur == sum) {
            cnt++;
        }
    }
    std::cout << ans << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    solve();
    return 0;
}
