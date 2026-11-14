#include <algorithm>
#include <iostream>
#include <string>

void solve() {
    std::string s;
    std::cin >> s;
    int res = 0;
    int mn = int(s.size());
    for (int i = 0; i < int(s.size()); i++) {
        int j = i;
        while (j < int(s.size()) && s[j] == 'A') {
            j++;
        }
        // 从 i 开始的一段连续 A。s[i] 本身是 B 时长度为 0，
        // 对应串首的 B，或连续 B 里多出来的那个 B。
        res += j - i;
        mn = std::min(mn, j - i);
        // 停在这段后面的 B 上，for 的 i++ 会跳过它。
        // 单个分隔用的 B 不会记成 0 段，第二个连续 B 才会。
        i = j;
    }
    // 以 B 结尾时，末尾这个 B 只会被 i++ 跳过。它没有右侧的 A 需要权衡，
    // 可以吃光左侧整段，不必牺牲任何 A 段。
    if (s.back() == 'B') {
        mn = 0;
    }
    res -= mn;
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
