#include <algorithm>
#include <iostream>
#include <string>

void solve() {
    std::string s;
    std::cin >> s;
    int x;
    std::cin >> x;
    int n = s.size();
    // '-' 表示尚未确定，'0' 表示被强制为 0
    std::string w(n, '-');

    // 强约束：s[i] == '0' 时，能影响它的两个位置都必须是 0
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            if (i - x >= 0) {
                w[i - x] = '0';
            }
            if (i + x < n) {
                w[i + x] = '0';
            }
        }
    }

    // 弱约束：s[i] == '1' 时，两个位置中至少有一个是 1
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            if (i - x >= 0 && w[i - x] != '0') {
                w[i - x] = '1';
            } else {
                if (i + x < n && w[i + x] != '0') {
                    w[i + x] = '1';
                } else {
                    // 两个来源都被强制为 0，无解
                    std::cout << -1 << '\n';
                    return;
                }
            }
        }
    }

    // 剩余位置填 1：它们的所有来源处 s 都是 1，填 1 不会产生矛盾
    for (int i = 0; i < n; i++) {
        if (w[i] == '-') {
            w[i] = '1';
        }
    }
    std::cout << w << '\n';
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
