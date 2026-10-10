#include <iostream>

using LL = long long;

const int N = int(2e5) + 5, MOD = int(1e9) + 7;

int n;
int A[N];
int factor[N];

void init() {
    factor[0] = 1;
    for (int i = 1; i < N; i++) {
        factor[i] = LL(factor[i - 1]) * i % MOD;
    }
}

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }
    // 全体元素的按位与；好序列的首尾都必须等于它
    int x = A[1];
    for (int i = 2; i <= n; i++) {
        x &= A[i];
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (x == A[i]) {
            cnt++;
        }
    }

    // 首尾各放一个等于 x 的元素，中间任意排：cnt * (cnt - 1) * (n - 2)!
    LL res = LL(cnt) * (cnt - 1) % MOD * factor[n - 2] % MOD;
    std::cout << res << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    init();

    int t = 1;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
