#include <iostream>
#include <string>

using LL = long long;

std::string codeforces = "codeforces";

LL fp(LL a, int b) {
    LL res = 1;
    while (b) {
        if (b & 1) {
            res = res * a;
        }
        a = a * a;
        b >>= 1;
    }
    return res;
}

void solve() {
    // k 最大到 1e16，必须用 64 位整数。
    LL k;
    std::cin >> k;
    // (x + 1)^10 >= k，且更小的全 x 乘积不够，段长只在 x 与 x + 1 之间。
    int x = 0;
    while (fp(x + 1, 10) < k) {
        x++;
    }
    // y 是长度为 x + 1 的段数，取最小的 y 使乘积达到 k。
    int y = 1;
    while (fp(x + 1, y) * fp(x, 10 - y) < k) {
        y++;
    }
    std::string res;
    for (int i = 0; i < y; i++) {
        res += std::string(x + 1, codeforces[i]);
    }
    for (int i = y; i < 10; i++) {
        res += std::string(x, codeforces[i]);
    }
    std::cout << res << '\n';
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
