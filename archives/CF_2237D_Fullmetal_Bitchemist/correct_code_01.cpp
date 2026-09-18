#include <algorithm>
#include <cstring>
#include <iostream>

using LL = long long;

const int N = int(1e6) + 5;

int n;
char S[N];
int cnt[3];

void solve() {
    std::cin >> n >> S;
    memmove(S + 1, S, n * sizeof(char));
    cnt[0] = 1; // 空前缀，权和 ≡ 0
    cnt[1] = cnt[2] = 0;
    int x = 0, y = 1;
    LL res = 0;
    for (int i = 1; i <= n; i++) {
        // 0→2、1→1：00→1、11→0 保持权和模 3 不变
        x += S[i] == '1' ? 1 : 2;
        x %= 3;
        // 以 i 结尾、权和 ≢ 0 的子串数
        res += cnt[0] + cnt[1] + cnt[2] - cnt[x];
        cnt[x]++;
        if (i > 1) {
            // y：以 i 结尾的最长严格交替后缀长度
            y = S[i] == S[i - 1] ? 1 : y + 1;
            // 减去长度 3,5,...,≤y 的交替后缀（偶数 y 时仍有奇数后缀）
            res -= (y - 1) / 2;
        }
    }
    std::cout << res << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
