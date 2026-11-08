#include <algorithm>
#include <iostream>
#include <vector>

const int N = 5010;

int gcd[N][N];

void init() { // gcd打表
    for (int i = 0; i < N; i++) {
        gcd[i][0] = gcd[0][i] = gcd[i][i] = i;
    }
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < i; j++) {
            gcd[i][j] = gcd[j][i] = gcd[j][i % j];
        }
    }
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> A(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> A[i];
    }

    // 全局 gcd 是操作不变量，最终所有数都等于它
    int resVal = A[1];
    for (int i = 2; i <= n; i++) {
        resVal = gcd[resVal][A[i]];
    }

    // 全部除以全局 gcd，目标变成「把所有数变成 1」
    for (int i = 1; i <= n; i++) {
        A[i] /= resVal;
    }
    int mx = *std::max_element(A.begin() + 1, A.end());
    // f[v] = 通过 gcd 合并凑出数值 v 所需的最少合并次数（已有的数代价为 0）
    std::vector<int> f(mx + 1, n);
    for (int i = 1; i <= n; i++) {
        f[A[i]] = 0;
    }
    // 倒序枚举状态：gcd(i, a) <= i，保证转移目标先被更新
    for (int i = mx; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            f[gcd[i][A[j]]] = std::min(f[gcd[i][A[j]]], f[i] + 1);
        }
    }
    // 凑出 1 需要 f[1] 次操作；1 本来就有时 f[1] = 0，公式同样成立
    int res = std::max(f[1] - 1, 0);
    for (int i = 1; i <= n; i++) { // 其余每个不等于 1 的元素各需 1 次操作
        res += A[i] != 1;
    }
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
